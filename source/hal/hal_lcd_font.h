#ifndef __HAL_LCD_FONT_H
#define __HAL_LCD_FONT_H

#include "lcd.h"
#include "dma.h"
#include "spi.h"

void hal_lcd_font_command(uint8_t dat);
uint8_t hal_lcd_font_get_data(void);
void hal_lcd_font_get_nbyte_data(uint8_t AddrHigh,uint8_t AddrMid,uint8_t AddrLow,uint8_t *pBuff,uint8_t DataLen);
void hal_lcd_font_GB2312(uint16_t x,uint16_t y,uint8_t zk_num,uint16_t fc,uint16_t bc);
void hal_lcd_font_GB2312_string(uint16_t x,uint16_t y,uint8_t zk_num,uint8_t text[],uint16_t fc,uint16_t bc);
void hal_lcd_font_asc(uint16_t x,uint16_t y,uint8_t zk_num,uint16_t fc,uint16_t bc);
void Display_Asc_string(uint16_t x,uint16_t y,uint16_t zk_num,uint8_t text[],uint16_t fc,uint16_t bc);
void hal_lcd_font_ascii_Arial_Roman(uint16_t x,uint16_t y,uint8_t zk_num,uint16_t fc,uint16_t bc);
void hal_lcd_font_ascii_Arial_string(uint16_t x,uint16_t y,uint16_t zk_num,uint8_t text[],uint16_t fc,uint16_t bc);
void hal_lcd_font_ascii_Roman_string(uint16_t x,uint16_t y,uint16_t zk_num,uint8_t text[],uint16_t fc,uint16_t bc);



#endif





