#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f4xx.h"
	 
void bsp_delay_init(void);
void bsp_systick_init(void);
void bsp_delay_ms(uint16_t nms);
void bsp_delay_us(uint32_t nus);

#endif
