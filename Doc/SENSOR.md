# Guía: Integración de Sensor de Temperatura

## Introducción

En esta guía, integraremos un sensor de temperatura al proyecto. Utilizaremos un sensor digital como el DS18B20 (One-Wire) o un termistor con ADC. Corresponde a la sesión sobre **Temp Sensor**, donde se implementa monitoreo ambiental para el sistema de control de sala.

## 1. Configuración de Periféricos en STM32CubeMX

### Opción 1: Sensor Digital (DS18B20 - One-Wire)

* Configura un pin GPIO como salida para el bus One-Wire (ej. **PB6**).
* No requiere ADC, comunicación bit-banging.

### Opción 2: Termistor con ADC

* Habilita el periférico **ADC1** en STM32CubeMX.
* Configura un canal ADC (ej. **PA0** como ADC1_IN5).
* Configuración ADC:
  * Mode: Single-ended
  * Sampling Time: 12.5 cycles
  * Resolution: 12-bit

## 2. Implementación de la Librería del Sensor

### sensor.h

```c
#ifndef SENSOR_H
#define SENSOR_H

#include "main.h"
#include <stdint.h>

typedef struct {
    ADC_HandleTypeDef *hadc;
    uint32_t channel;
} adc_sensor_handle_t;

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} onewire_sensor_handle_t;

void adc_sensor_init(adc_sensor_handle_t *sensor);
float adc_sensor_read_temperature(adc_sensor_handle_t *sensor);

void onewire_sensor_init(onewire_sensor_handle_t *sensor);
float onewire_sensor_read_temperature(onewire_sensor_handle_t *sensor);

#endif // SENSOR_H
```

### sensor.c (Ejemplo con ADC)

```c
#include "sensor.h"

#define ADC_RESOLUTION 4096.0f  // 12-bit
#define VREF 3.3f

void adc_sensor_init(adc_sensor_handle_t *sensor) {
    // Inicialización si es necesaria
}

float adc_sensor_read_temperature(adc_sensor_handle_t *sensor) {
    HAL_ADC_Start(sensor->hadc);
    HAL_ADC_PollForConversion(sensor->hadc, HAL_MAX_DELAY);
    uint32_t adc_value = HAL_ADC_GetValue(sensor->hadc);

    // Conversión simplificada (ajusta según tu termistor)
    float voltage = (adc_value / ADC_RESOLUTION) * VREF;
    float temperature = (voltage - 0.5f) * 100.0f;  // Ejemplo LM35

    return temperature;
}
```

## 3. Integración en main.c

```c
#include "sensor.h"

adc_sensor_handle_t temp_sensor = { .hadc = &hadc1, .channel = ADC_CHANNEL_5 };

int main(void) {
    // ...
    adc_sensor_init(&temp_sensor);

    while (1) {
        float temp = adc_sensor_read_temperature(&temp_sensor);
        // Procesar temperatura...
    }
}
```

## 4. Ejercicio

Implementa la lectura de temperatura y muestra el valor en el display OLED.

## Integración al Proyecto "Control de Sala"

El sensor de temperatura será el componente de monitoreo principal, activando el ventilador cuando supere un umbral configurable vía teclado.

**Siguiente Paso:** [Control de Ventilador PWM (Doc/FAN.md)](FAN.md)