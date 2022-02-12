#ifndef __LED_H
#define __LED_H

#include "gd32f1x0.h"
#include "stdio.h"

#define LED_RCC  RCU_GPIOB
#define LED_PORT GPIOB
#define LED1_PIN  GPIO_PIN_1
#define LED2_PIN  GPIO_PIN_2

#define LED1    (1)
#define LED2    (2)
#define LED_ON  (1)
#define LED_OFF (0)
void bsp_led_init(void);
uint8_t bsp_led_control(uint8_t led,uint8_t state);
#endif 
