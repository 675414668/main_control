#include "hal.h"
#include "version.h"
#include "task_lcd.h"

int main(void)
{
	hal_init();
	hal_usart_init();
	hal_delay_init();
	hal_led_init();
	hal_key_init();
	task_lcd_init();
	
  printf("HARDWARE_VERSION:%s\r\n",HARDWARE_VERSION);
	printf("SOFTWARE_VERSION:%s\r\n",SOFTWARE_VERSION);
    while(1)
		{
			task_lcd_display();
    }
}


