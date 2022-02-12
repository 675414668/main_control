#include "hal.h"
#include "version.h"
#include "task_lcd.h"
#include "task_led.h"

int main(void)
{
	hal_sys_clk_init();
	hal_delay_init();
	hal_usart_init(115200);
	hal_flash_user_data_init();
	task_led_init();
  task_lcd_init();
	
	printf("system begin\r\n");
//	printf("cpu frequency:%d\r\n",hal_get_clock_frequency(SYSCLK_FREQUENCY));
  printf("HARDWARE_VERSION:%s\r\n",HARDWARE_VERSION);
	printf("SOFTWARE_VERSION:%s\r\n",SOFTWARE_VERSION);
    while(1)
		{
			task_key_scan();
			task_lcd_display();
			task_led();
    }
}


