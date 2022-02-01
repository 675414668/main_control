#include "hal_sys_clk.h"

void hal_sys_clk_init(void)
{
	bsp_sys_clk_init();
}

uint32_t hal_get_clock_frequency(uint8_t clk)
{
	return bsp_get_clock_frequency(clk);
}
