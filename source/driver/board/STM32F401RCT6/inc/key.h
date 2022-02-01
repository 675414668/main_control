#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include "string.h"

#define KEY_RCC   RCC_AHB1Periph_GPIOC
#define KEY_PORT  GPIOC
#define KEY1_PIN  GPIO_Pin_2
#define KEY2_PIN  GPIO_Pin_0
#define KEY3_PIN  GPIO_Pin_1

#define KEY_TIM                TIM3
#define KEY_TIM_RCC            RCC_APB1Periph_TIM3
#define KEY_TIM_PERIOD         (10000)
#define KEY_TIM_PRESCALER      (84-1)
#define KEY_TIM_IRQN           TIM3_IRQn
#define KEY_TIM_IRQHANDLER     TIM3_IRQHandler

//TIM_OUT = KEY_TIM_PERIOD*(KEY_TIM_PRESCALER+1)/84 =10MS

void bsp_key_init(void);
uint8_t bsp_get_key_press(void);
#endif 
