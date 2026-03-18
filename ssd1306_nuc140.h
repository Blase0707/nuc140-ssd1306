/**
 * original author:  Tilen Majerle<tilen@majerle.eu>
 * modification for STM32f10x: Alexander Lutsai<s.lyra@ya.ru>
 * Ported to Nuvoton NUC140: Blase0707<oscarwang23745508@gmail.com>, 2026
 * 
 * This file is a modified version of the original ssd1306.c
 * from https://github.com/SL-RU/stm32libs/blob/master/HAL/ssd1306/ssd1306.c

   ----------------------------------------------------------------------
    Copyright (C) LC Wang, 2026
   	Copyright (C) Alexander Lutsai, 2016
    Copyright (C) Tilen Majerle, 2015

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
 */

/**
 * SSD1306 OLED Driver for Nuvoton NUC140
 * Ported from STM32 HAL version
 * 
 * I2C0 Configuration:
 * - SDA: PA8
 * - SCL: PA9
 * - Speed: 100kHz
 */
#ifndef SSD1306_NUC140_H
#define SSD1306_NUC140_H

#ifdef __cplusplus
extern "C" {
#endif

#include "NUC100Series.h"
#include "fonts.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

/* I2C address */
#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR         0x78
//#define SSD1306_I2C_ADDR       0x7A
#endif

/* SSD1306 settings */
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH            128
#endif

#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT           64
#endif

/* I2C timeout in ms */
#ifndef SSD1306_I2C_TIMEOUT
#define SSD1306_I2C_TIMEOUT      100
#endif

/**
 * @brief  SSD1306 color enumeration
 */
typedef enum {
    SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
    SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;

/**
 * @brief  Initializes SSD1306 LCD
 * @retval Initialization status:
 *           - 0: LCD was not detected on I2C port
 *           - > 0: LCD initialized OK and ready to use
 */
uint8_t SSD1306_Init(void);

/** 
 * @brief  Updates buffer from internal RAM to LCD
 * @note   This function must be called each time you do some changes to LCD
 */
void SSD1306_UpdateScreen(void);

/**
 * @brief  Toggles pixels invertion inside internal RAM
 */
void SSD1306_ToggleInvert(void);

/** 
 * @brief  Fills entire LCD with desired color
 * @param  Color: Color to be used for screen fill
 */
void SSD1306_Fill(SSD1306_COLOR_t Color);

/**
 * @brief  Draws pixel at desired location
 * @param  x: X location (0 to SSD1306_WIDTH - 1)
 * @param  y: Y location (0 to SSD1306_HEIGHT - 1)
 * @param  color: Color to be used
 */
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);

/**
 * @brief  Sets cursor pointer to desired location for strings
 * @param  x: X location (0 to SSD1306_WIDTH - 1)
 * @param  y: Y location (0 to SSD1306_HEIGHT - 1)
 */
void SSD1306_GotoXY(uint16_t x, uint16_t y);

/**
 * @brief  Puts character to internal RAM
 * @param  ch: Character to be written
 * @param  *Font: Pointer to FontDef_t structure with used font
 * @param  color: Color used for drawing
 * @retval Character written
 */
char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);

/**
 * @brief  Puts string to internal RAM
 * @param  *str: String to be written
 * @param  *Font: Pointer to FontDef_t structure with used font
 * @param  color: Color used for drawing
 * @retval Zero on success or character value when function failed
 */
char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);

/**
 * @brief  Draws line on LCD
 */
void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);

/**
 * @brief  Draws rectangle on LCD
 */
void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

/**
 * @brief  Draws filled rectangle on LCD
 */
void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

/**
 * @brief  Draws triangle on LCD
 */
void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);

/**
 * @brief  Draws filled triangle on LCD
 */
void SSD1306_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);

/**
 * @brief  Draws circle on LCD
 */
void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

/**
 * @brief  Draws filled circle on LCD
 */
void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

/**
 * @brief  Draws bitmap on LCD
 */
void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);

/**
 * @brief  Scroll functions
 */
void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row);
void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row);
void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row);
void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row);
void SSD1306_Stopscroll(void);

/**
 * @brief  Inverts the display
 * @param  i: 1 = inverted, 0 = normal
 */
void SSD1306_InvertDisplay(int i);

/**
 * @brief  Clear the display
 */
void SSD1306_Clear(void);

/**
 * @brief  Turn ON the display
 */
void SSD1306_ON(void);

/**
 * @brief  Turn OFF the display
 */
void SSD1306_OFF(void);

/* Low-level I2C functions - Internal use */
void SSD1306_I2C_Init(void);
int SSD1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
int SSD1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);
int SSD1306_I2C_IsDeviceReady(uint8_t address);

/* I2C Interrupt Handler - Must be called in I2C0_IRQHandler */
void SSD1306_I2C0_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* SSD1306_NUC140_H */
