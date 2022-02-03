#ifndef __HAL_KEY_H
#define __HAL_KEY_H

#include "key.h"

void hal_key_init(void);
uint8_t hal_get_key_press(void);
void hal_set_key_press(uint8_t state);
uint8_t hal_lcd_get_astronaut_image_num(void);
#endif 
