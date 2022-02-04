#ifndef __HAL_LCD_H
#define __HAL_LCD_H

#include "lcd.h"

void hal_lcd_init(void);
void hal_key_init(void);
uint8_t hal_get_key_press(void);
void hal_set_key_press(uint8_t state);
uint8_t hal_lcd_get_astronaut_image_num(void);
uint8_t hal_lcd_get_waiting_time(void);
#endif





