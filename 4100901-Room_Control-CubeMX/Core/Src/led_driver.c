#include "led_driver.h"

void led_init(led_handle_t *led) //funcion que incializa led 
{
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
}

void led_on(led_handle_t *led) //funcion que enciende led 
{
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
}

void led_off(led_handle_t *led) // funcion que apaga led 
{
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
}

void led_toggle(led_handle_t *led) //funcion que cambia el estado del led
{
    HAL_GPIO_TogglePin(led->port, led->pin);
}