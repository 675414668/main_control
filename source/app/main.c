#include "hal_delay.h"
#include "hal_led.h"
#include "hal_key.h"
#include "task_lcd.h"

int main(void)
{
	hal_delay_init();
	hal_led_init();
	hal_key_init();
	task_lcd_init();
    while(1)
		{
			task_lcd_display();
    }
}


