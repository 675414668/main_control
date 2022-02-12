#ifndef __USART_H
#define __USART_H
#include "gd32f1x0.h"
#include "stdio.h"
#include "string.h"

#define USART_COM              USART0
#define USART_COM_RCU          RCU_USART0
#define USART_COM_IRQn         USART1_IRQn
#define USART_COM_PORT         GPIOB
#define RCU_USART_COM_PORT     RCU_GPIOB
#define USART_COM_TX_PIN       GPIO_PIN_6
#define USART_COM_RX_PIN       GPIO_PIN_7

void bsp_usart_com_init(uint32_t boadrate);
#endif
