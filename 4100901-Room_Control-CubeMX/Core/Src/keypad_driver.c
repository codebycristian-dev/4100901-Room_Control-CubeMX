#include "keypad_driver.h"

// Mapa: [[1,2,3,A],[4,5,6,B],[7,8,9,C],[*,0,#,D]]
static const char keypad_map[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Dead-time global para suavizar rebotes que generan múltiples EXTI
#ifndef KEYPAD_DEBOUNCE_MS
#define KEYPAD_DEBOUNCE_MS 250u //definimos tiempo para el debounce
#endif
/**
 * @brief Inicializa el keypad poniendo las filas en estado inactivo (BAJO)
 * @param kp Puntero a la estructura del keypad
 * @return void 
 */
void keypad_init(keypad_handle_t *kp)
{
    // Filas inactivas (BAJO)
    for (int r = 0; r < KEYPAD_ROWS; ++r)
    {
        HAL_GPIO_WritePin(kp->row_ports[r], kp->row_pins[r], GPIO_PIN_RESET);
    }
}
/**
 * @brief Escanea el keypad para detectar qué tecla se ha presionado
 * @param kp Puntero a la estructura del keypad
 * @param col_pin Pin de la columna que disparó la interrupción EXTI
 * @return Carácter de la tecla presionada, o '\0' si no se detecta ninguna
 */
char keypad_scan(keypad_handle_t *kp, uint16_t col_pin)
{
    /**
     * @note Debounce simple basado en tiempo: si se llama a esta función
     * dentro del intervalo de debounce desde la última tecla válida
     */
    static uint32_t last_tick = 0; // debounce no bloqueante
    uint32_t now = HAL_GetTick();
    if ((now - last_tick) < KEYPAD_DEBOUNCE_MS)
    {
        return '\0';
    }

    // 1) Identificar columna por el pin recibido desde la EXTI
    int col = -1;
    for (int c = 0; c < KEYPAD_COLS; ++c)
    {
        if (kp->col_pins[c] == col_pin)
        {
            col = c;
            break;
        }
    }
    if (col < 0)
        return '\0'; // pin ajeno al keypad

    /**
     * @note Escaneo de filas:
     *  - Poner todas las filas en ALTO (inactivas)
     * - Activar una fila a la vez (ponerla en BAJO) y leer la columna que disparó
     * - Si la columna está en BAJO, esa es la tecla presionada
     * - Restaurar la fila a ALTO antes de continuar
     * - Al final, dejar todas las filas en BAJO (estado inactivo)
     * - Retornar el carácter de la tecla encontrada, o '\0' si no se detecta ninguna
     */
    for (int r = 0; r < KEYPAD_ROWS; ++r)
    {
        HAL_GPIO_WritePin(kp->row_ports[r], kp->row_pins[r], GPIO_PIN_SET);
    }

    // 3) Activar una fila a la vez (LOW) y leer SOLO la columna que disparó
    char key = '\0';
    for (int r = 0; r < KEYPAD_ROWS; ++r)
    {
        HAL_GPIO_WritePin(kp->row_ports[r], kp->row_pins[r], GPIO_PIN_RESET); // fila activa (LOW)
        __ASM volatile("nop; nop; nop; nop;");                                // pequeño settle (~tens de ns)

        if (HAL_GPIO_ReadPin(kp->col_ports[col], kp->col_pins[col]) == GPIO_PIN_RESET)
        {
            key = keypad_map[r][col];
            HAL_GPIO_WritePin(kp->row_ports[r], kp->row_pins[r], GPIO_PIN_SET);
            break;
        }

        // restaurar fila antes de continuar
        HAL_GPIO_WritePin(kp->row_ports[r], kp->row_pins[r], GPIO_PIN_SET);
    }

    /**
     * @note Restaurar todas las filas a estado inactivo (LOW)
     * @note Actualizar el tick del último evento válido si se detectó una tecla
     * @note Retornar la tecla detectada o '\0' si no se detectó ninguna
     */
    for (int r = 0; r < KEYPAD_ROWS; ++r)
    {
        HAL_GPIO_WritePin(kp->row_ports[r], kp->row_pins[r], GPIO_PIN_RESET);
    }

    if (key != '\0')
    {
        last_tick = now; // aplicar dead-time sólo cuando hay tecla válida
    }
    return key;
}
