#ifndef __HAL_DELAY_H
#define __HAL_DELAY_H

#include "delay.h"

void hal_delay_init(void);
void hal_delay_us(uint32_t nus);
void hal_delay_ms(uint16_t nms);
#endif 


