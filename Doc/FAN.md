# Guía: Control de Ventilador con PWM

## Introducción

En esta guía, implementaremos el control de un ventilador utilizando PWM (Pulse Width Modulation). Esto permite regular la velocidad del ventilador de manera eficiente. Corresponde a la sesión sobre **Fan**, donde se aplica control PWM para sistemas de ventilación.

## 1. Configuración de PWM en STM32CubeMX

* Habilita el periférico **TIM2** (o cualquier timer disponible).
* Configura un canal como **PWM Generation** (ej. **Channel 1** en **PA5**).
* Parámetros PWM:
  * Prescaler: 79 (para 1MHz con reloj de 80MHz)
  * Counter Period: 999 (para frecuencia de 1kHz)
  * Pulse: Variable (0-999 para duty cycle 0-100%)

## 2. Implementación de la Librería del Ventilador

### fan.h

```c
#ifndef FAN_H
#define FAN_H

#include "main.h"
#include <stdint.h>

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
} fan_handle_t;

void fan_init(fan_handle_t *fan);
void fan_set_speed(fan_handle_t *fan, uint8_t percentage);
void fan_start(fan_handle_t *fan);
void fan_stop(fan_handle_t *fan);

#endif // FAN_H
```

### fan.c

```c
#include "fan.h"

void fan_init(fan_handle_t *fan) {
    HAL_TIM_PWM_Start(fan->htim, fan->channel);
}

void fan_set_speed(fan_handle_t *fan, uint8_t percentage) {
    if (percentage > 100) percentage = 100;

    uint32_t pulse = (percentage * (fan->htim->Init.Period + 1)) / 100;
    __HAL_TIM_SET_COMPARE(fan->htim, fan->channel, pulse);
}

void fan_start(fan_handle_t *fan) {
    HAL_TIM_PWM_Start(fan->htim, fan->channel);
}

void fan_stop(fan_handle_t *fan) {
    HAL_TIM_PWM_Stop(fan->htim, fan->channel);
}
```

## 3. Integración en main.c

```c
#include "fan.h"

fan_handle_t fan = { .htim = &htim2, .channel = TIM_CHANNEL_1 };

int main(void) {
    // ...
    fan_init(&fan);
    fan_set_speed(&fan, 50);  // 50% duty cycle

    while (1) {
        // Control basado en temperatura...
    }
}
```

## 4. Ejercicio

Implementa control automático del ventilador basado en la temperatura leída del sensor.

## Integración al Proyecto "Control de Sala"

El ventilador PWM será controlado automáticamente por el sistema: bajo velocidad para temperaturas moderadas, alta velocidad para temperaturas elevadas, y apagado cuando no sea necesario.

**Siguiente Paso:** [Conexión IoT con ESP01 (Doc/ESP01.md)](ESP01.md)