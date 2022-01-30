#ifndef __HAL_USART_H
#define __HAL_USART_H

#include "usart.h"
#include "timer.h"

void hal_usart_init(void);
void hal_uasrt_hex_display(uint8_t* lcd_data);
void hal_uasrt_dec_display(uint8_t* lcd_data);
#endif 


