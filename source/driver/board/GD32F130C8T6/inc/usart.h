#ifndef __USART_H
#define __USART_H
#include "gd32f1x0.h"
#include "stdio.h"
#include "string.h"

void bsp_usart_init(void);
uint8_t bsp_get_usart_rx_flag(void);
void bsp_clear_usart_rx_flag(void);
void bsp_get_usart_rx_data(uint8_t *data);
uint8_t bsp_get_usart_rx_count (void);
void bsp_clear_usart_rx_count (void);
void bsp_clear_usart_rx_buff (void);
#endif
