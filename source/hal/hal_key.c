#include "hal_key.h"

void hal_key_init(void)
{
	bsp_key_init();
}

uint8_t hal_get_key_press(void)
{
	return bsp_get_key_press();
}
