# SSD1306 OLED Driver for Nuvoton NUC140

## Overview

This is a port of the SSD1306 OLED display driver to the Nuvoton NUC140 microcontroller. The driver provides a complete set of APIs for controlling 128x64 OLED displays via I2C interface, including pixel drawing, text rendering, geometric shapes, and scrolling effects.

Based on the original work by Tilen Majerle and the STM32 modifications by Alexander Lutsai, adapted for NUC140 standard driver library.

**License:** GNU General Public License v3.0 or later (GPL-3.0-or-later)

## Hardware Connections

### SSD1306 OLED Display to NUC140

| OLED Pin | NUC140 Pin | Function |
|----------|-----------|----------|
| GND      | GND       | Ground   |
| VCC      | 3.3V      | Power    |
| SDA      | PA8       | I2C0 Data Line |
| SCL      | PA9       | I2C0 Clock Line |

**I2C Configuration:**
- **Bus:** I2C0
- **Speed:** 100 kHz (Standard mode)
- **Default Display Address:** 0x78 (alternative: 0x7A)

## Hardware Setup

![](image.png)
