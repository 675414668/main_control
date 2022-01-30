#ifndef __DELAY_H
#define __DELAY_H 			   
#include "gd32f1x0.h"

void bsp_delay_init(void);
void bsp_delay_ms(uint16_t nms);
void bsp_delay_us(uint32_t nus);

#endif
