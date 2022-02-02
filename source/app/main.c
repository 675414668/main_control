#include "hal.h"
#include "version.h"
#include "task_lcd.h"
#include "task_led.h"

int main(void)
{
	hal_sys_clk_init();
	hal_delay_init();
	hal_usart_init(115200);
	task_led_init();
	hal_key_init();
  task_lcd_init();
	
	printf("system begin\r\n");
	printf("cpu frequency:%d\r\n",hal_get_clock_frequency(SYSCLK_FREQUENCY));
  printf("HARDWARE_VERSION:%s\r\n",HARDWARE_VERSION);
	printf("SOFTWARE_VERSION:%s\r\n",SOFTWARE_VERSION);
    while(1)
		{
			task_lcd_display();
			task_led();
    }
}


