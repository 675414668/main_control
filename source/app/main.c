#include "hal_delay.h"
#include "hal_led.h"


int main(void)
{
	hal_delay_init();
	hal_led_init();
	
    while(1)
		{
			hal_led_control(LED1,LED_ON);
			hal_led_control(LED2,LED_OFF);
			hal_delay_ms(500);
			hal_led_control(LED1,LED_OFF);
			hal_led_control(LED2,LED_ON);
			hal_delay_ms(500);
    }
}


