# STM32-Temperature-Monitoring-System
A temperature monitoring system built with the STM32F103RB microcontroller, BMP180 sensor, and SSD1306. The project demonstrates embedded C programming, I²C communication, UART serial output, sensor data processing, and custom OLED display routines using the STM32 HAL library. OLED display.

# Features
- Temperature measurement using the BMP180 sensor

- I²C communication with both the BMP180 and SSD1306

- Real-time temperature display on a 128×64 OLED

- UART serial output for monitoring and debugging

- Custom 5×7 bitmap font for displaying numeric values

- Modular firmware organization using separate sensor and display driver files


# Hardware Components
Microcontroller          STM32 NUCLEO-F103RB

Temperature sensor          BMP180

Display | SSD1306 128×64 OLED

Communication | I²C1, USART2

Debugger | Onboard ST-LINK
