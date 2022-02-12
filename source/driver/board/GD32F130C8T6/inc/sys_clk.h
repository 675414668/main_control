#ifndef __SYS_CLK_H
#define __SYS_CLK_H

#include "gd32f1x0.h"
#include "string.h"


uint8_t bsp_sys_clk_init(void);
uint32_t bsp_get_clock_frequency(uint8_t clk);
#endif 
