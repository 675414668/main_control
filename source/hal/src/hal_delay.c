#include "hal_delay.h"

void hal_delay_init(void)
{
	bsp_delay_init();
}

void hal_delay_us(uint32_t us)
{
	bsp_delay_us(us);
}
void hal_delay_ms(uint16_t ms)
{
	 bsp_delay_ms(ms);
}
