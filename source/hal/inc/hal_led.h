#ifndef __HAL_LED_H
#define __HAL_LED_H

#include "led.h"

void hal_led_init(void);
uint8_t hal_led_control(uint8_t led,uint8_t state);
#endif 


