#include "hal_timer.h"

void hal_timer_init(void)
{
  bsp_timer_init();
}

void hal_timer_display(uint8_t *data)
{
	bsp_get_sys_time_buff(data);
}

