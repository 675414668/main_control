#include "hal_led.h"

void hal_led_init(void)
{
   bsp_led_init();
}

uint8_t hal_led_control(uint8_t led,uint8_t state)
{
	return bsp_led_control(led,state);
}

