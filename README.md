# Segunda Fase del Curso: Estructuras Computacionales

**Universidad Nacional de Colombia - Sede Manizales**

**Curso:** Estructuras Computacionales (4100901)

## Introducción

En esta segunda fase del curso **Estructuras Computacionales**, nos enfocaremos en la **implementación de los componentes fundamentales de un dispositivo computacional**. El propósito principal es fortalecer las habilidades en la creación y reutilización de drivers/librerías, así como en la integración de componentes de entrada/salida (I/O).

Los conocimientos adquiridos se aplicarán **progresivamente** en la construcción del proyecto final llamado **"Control de Sala"**, un sistema embebido que integra:

* Un teclado Hexadecimal para entrada de comandos.
* Un display OLED (SSD1306) para visualización de estado.
* Un sensor de temperatura para monitoreo ambiental.
* Un sistema de ventilación controlado por PWM.
* Conexión a Internet mediante el módulo ESP01 para telemetría.

Este proyecto se desarrolla de manera incremental a lo largo de las sesiones, permitiendo a los estudiantes ver el panorama completo al finalizar las guías.

## Objetivos Específicos

* Comprender y dominar el uso de STM32CubeMX para la configuración inicial de proyectos.
* Aprender los principios y la estructura de librerías modulares en C.
* Implementar componentes como GPIO, UART, Timers, Buffers circulares, y periféricos avanzados (ADC, PWM, I2C).
* Integrar estos componentes para construir sistemas robustos y reutilizables.
* Aplicar técnicas de optimización en memoria, tiempo de ejecución y consumo energético.

## Guías Progresivas del Proyecto "Control de Sala"

Este repositorio contiene guías secuenciales que siguen el cronograma del curso, construyendo el proyecto paso a paso:

* [`Doc/SETUP.md`](Doc/SETUP.md): Configuración del entorno de desarrollo (Sesiones: Introducción, Repaso de Sistemas Digitales).
* [`Doc/CUBEMX_CONFIG.md`](Doc/CUBEMX_CONFIG.md): Configuración de STM32CubeMX y periféricos básicos (GPIOs, UART, NVIC).
* [`Doc/LIB_PRINCIPLES.md`](Doc/LIB_PRINCIPLES.md): Principios de librerías modulares y programación estructurada.
* [`Doc/RING_BUFFER.md`](Doc/RING_BUFFER.md): Implementación de buffer circular para UART (Sesión: Librerías).
* [`Doc/KEYPAD.md`](Doc/KEYPAD.md): Driver para teclado hexadecimal (Sesión: Teclado).
* [`Doc/SSD1306.md`](Doc/SSD1306.md): Integración de display OLED (Sesión: LCD).
* [`Doc/OPTIMIZATION.md`](Doc/OPTIMIZATION.md): Técnicas de optimización (Sesiones: Memoria, Tiempo, Energía).
* [`Doc/SENSOR.md`](Doc/SENSOR.md): Sensor de temperatura (Sesión: Temp Sensor).
* [`Doc/FAN.md`](Doc/FAN.md): Control de ventilador PWM (Sesión: Fan).
* [`Doc/ESP01.md`](Doc/ESP01.md): Conexión IoT con ESP01 (Sesión: Introducción a IoT).

Cada guía incluye ejercicios prácticos, integración al proyecto "Control de Sala", y referencias al siguiente paso.

---

¡Manos a la obra! Comienza por revisar la [Configuración del Entorno (Doc/SETUP.md)](Doc/SETUP.md).
