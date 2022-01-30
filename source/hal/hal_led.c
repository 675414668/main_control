#include "hal_led.h"

void hal_led_init(void)
{
   bsp_led_init();
}

void hal_led_test_on(void)
{
	bsp_led_test_on();
}

void hal_led_test_off(void)
{
	bsp_led_test_off();
}
