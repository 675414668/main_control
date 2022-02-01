#include "hal.h"
#include "task_lcd.h"

int main(void)
{
	hal_init();
	hal_delay_init();
	hal_led_init();
	hal_key_init();
	task_lcd_init();
    while(1)
		{
			task_lcd_display();
    }
}


