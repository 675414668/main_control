#ifndef __HAL_SYS_CLK_H
#define __HAL_SYS_CLK_H

#include "sys_clk.h"

void hal_sys_clk_init(void);
uint32_t hal_get_clock_frequency(uint8_t clk);
#endif 
