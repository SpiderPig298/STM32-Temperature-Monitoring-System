# STM32-Temperature-Monitoring-System
A temperature monitoring system built with the STM32F103RB microcontroller, BMP180 sensor, and SSD1306. The project demonstrates embedded C programming, I²C communication, UART serial output, sensor data processing, and custom OLED display routines using the STM32 HAL library. OLED display.

# Features
- Temperature measurement using the BMP180 sensor

- I²C communication with both the BMP180 and SSD1306

- Real-time temperature display on a 128×64 OLED

- UART serial output for monitoring and debugging

- Custom 5×7 bitmap font for displaying numeric values

- Modular firmware organization using separate sensor and display driver files


# Components and tools
<table>
  <tr>
    <th colspan="2">Hardware</th>
  </tr>
  <tr>
    <td>Microcontroller</td>
    <td>STM32 NUCLEO-F103RB</td>
  </tr>
  <tr>
    <td>Temperature sensor</td>
    <td>BMP180</td>
  </tr>
  <tr>
    <td>Display</td>
    <td>SSD1306 128×64 OLED</td>
  </tr>
  <tr>
    <td>Communication</td>
    <td>I²C1, USART2</td>
  </tr>
  <tr>
    <td>Debugger</td>
    <td>Onboard ST-LINK</td>
    
  </tr>
  <tr>
    <th colspan="2">Software</th>
  </tr>
  <tr colsapn="2"><td>STM32CubeIDE</td></tr>
  <tr colsapn="2"><td>STM32CubeMX peripheral configuration</td></tr>
  <tr colsapn="2"><td>STM32 HAL Driver</td></tr>

</table>

# Firmware Implementation

## 1. BMP180 Sensor Interface

<p>Implemented I²C register communication using STM32 HAL functions.

Initiated temperature measurements and retrieved sensor data.

Processed raw sensor readings for temperature output.</p>

## 2. SSD1306 OLED Driver

<p>Implemented OLED initialization and display control commands.

Configured horizontal addressing and page/column ranges.

Developed routines for writing display data and clearing the screen.

Implemented a custom 5×7 numeric bitmap font, including decimal-point rendering.</p>

## 3. UART Communication

<p>Configured USART2 for serial communication.

Transmitted temperature readings to a computer for monitoring.

Used serial output to support firmware debugging and verification.</p>

## Project Demonstration



BMP180 temperature reading displayed on the SSD1306 OLED.
