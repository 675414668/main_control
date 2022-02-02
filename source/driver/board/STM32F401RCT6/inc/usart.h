#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include "stdio.h"

#define USART_COM              USART1
#define USART_COM_IRQn         USART1_IRQn
#define USART_COM_PORT         GPIOA
#define USART_COM_TX_SOURCE    GPIO_PinSource9
#define USART_COM_RX_SOURCE    GPIO_PinSource10
#define USART_COM_TX_PIN       GPIO_Pin_9
#define USART_COM_RX_PIN       GPIO_Pin_10

void bsp_usart_com_init(uint32_t boadrate);
#endif 
