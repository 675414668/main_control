#include "hal_lcd.h"

void hal_lcd_init(void)
{
	bsp_lcd_init();
}
void hal_key_init(void)
{
	bsp_key_init();
}
uint8_t hal_get_key_press(void)
{
	return bsp_get_key_press();
}

void hal_set_key_press(uint8_t state)
{
	bsp_set_key_press(state);
}

uint8_t hal_lcd_get_astronaut_image_num(void)
{
	return  bsp_lcd_get_astronaut_image_num();
}

uint8_t hal_lcd_get_waiting_time(void)
{
	return bsp_lcd_get_waiting_time();
}

void hal_get_stopwatch_timebuff(uint8_t *data)
{
	bsp_get_stopwatch_timebuff(data);
}
void hal_stopwatch_timebuff_clear(void)
{
	bsp_stopwatch_timebuff_clear();
}

void hal_stopwatch_ctrl(uint8_t state)
{
	bsp_stopwatch_ctrl(state);
}
