#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"
	 
void bsp_delay_init(void);
void bsp_systick_init(void);
void bsp_delay_ms(u16 nms);
void bsp_delay_us(u32 nus);

#endif
