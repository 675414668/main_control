#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"
#include "string.h"

#define LED_RCC   RCC_AHB1Periph_GPIOC
#define LED_PORT  GPIOC
#define LED1_PIN  GPIO_Pin_4
#define LED2_PIN  GPIO_Pin_5

#define LED1    (1)
#define LED2    (2)
#define LED_ON  (1)
#define LED_OFF (0)
void bsp_led_init(void);
uint8_t bsp_led_control(uint8_t led,uint8_t state);
#endif 
