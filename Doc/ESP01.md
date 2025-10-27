# Guía: Conexión IoT con ESP01

## Introducción

En esta guía, integraremos el módulo ESP01 para conectividad WiFi, permitiendo telemetría y control remoto. Corresponde a la sesión sobre **Introducción a IoT (Demo: ESP01-Telnet)**, donde se demuestra comunicación inalámbrica básica.

## 1. Configuración del ESP01

* Conecta el ESP01 a UART adicional (ej. **USART1** en **PA9/PA10**).
* Alimentación: 3.3V (usa regulador si es necesario).
* Configura el ESP01 en modo station/client.

## 2. Comunicación con ESP01

### Configuración UART en STM32CubeMX

* Habilita **USART1** como Asynchronous.
* Baud Rate: 115200
* Interrupciones: RX habilitada

### Librería Básica para ESP01

#### esp01.h

```c
#ifndef ESP01_H
#define ESP01_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    UART_HandleTypeDef *huart;
} esp01_handle_t;

void esp01_init(esp01_handle_t *esp);
bool esp01_connect_wifi(esp01_handle_t *esp, const char *ssid, const char *password);
bool esp01_send_data(esp01_handle_t *esp, const char *data);
bool esp01_receive_data(esp01_handle_t *esp, char *buffer, uint16_t size);

#endif // ESP01_H
```

#### esp01.c

```c
#include "esp01.h"
#include <string.h>

void esp01_init(esp01_handle_t *esp) {
    // Reset ESP01 si es necesario
    HAL_UART_Transmit(esp->huart, (uint8_t*)"AT+RST\r\n", 8, HAL_MAX_DELAY);
    HAL_Delay(2000);
}

bool esp01_connect_wifi(esp01_handle_t *esp, const char *ssid, const char *password) {
    char cmd[64];
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    HAL_UART_Transmit(esp->huart, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);

    // Esperar respuesta (simplificado)
    HAL_Delay(5000);
    return true;  // Verificar respuesta real
}

bool esp01_send_data(esp01_handle_t *esp, const char *data) {
    // Enviar datos vía TCP/UDP (configurar servidor primero)
    char cmd[128];
    sprintf(cmd, "AT+CIPSEND=%d\r\n", strlen(data));
    HAL_UART_Transmit(esp->huart, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(esp->huart, (uint8_t*)data, strlen(data), HAL_MAX_DELAY);

    return true;
}
```

## 3. Integración en main.c

```c
#include "esp01.h"

esp01_handle_t wifi = { .huart = &huart1 };

int main(void) {
    // ...
    esp01_init(&wifi);
    esp01_connect_wifi(&wifi, "MiWiFi", "password123");

    while (1) {
        // Enviar telemetría periódicamente
        char telemetry[32];
        sprintf(telemetry, "Temp: %.1f C\r\n", current_temp);
        esp01_send_data(&wifi, telemetry);
        HAL_Delay(60000);  // Cada minuto
    }
}
```

## 4. Ejercicio

Configura el ESP01 para enviar datos de temperatura a un servidor remoto o app móvil.

## Integración al Proyecto "Control de Sala"

El ESP01 permitirá monitoreo remoto de la sala: recibir lecturas de temperatura, enviar alertas, y potencialmente recibir comandos de control remoto.

**Proyecto Final Completo:** Integra todos los componentes (teclado, display, sensor, ventilador, ESP01) en un sistema coherente de "Control de Sala".