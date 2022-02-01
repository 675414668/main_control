#include "task_led.h"

typedef struct 
{
	uint8_t led1;
	uint8_t led2;
}led_state_t;
led_state_t led_state;

static void led_data_init(void);

void task_led_init(void)
{
	hal_led_init();
	led_data_init();
}

static void led_data_init(void)
{
	led_state.led1 = LED_OFF;
	led_state.led2 = LED_ON;
}

void task_led(void)
{
	if(led_state.led1 == LED_ON)
	{
	 hal_led_control(LED1,LED_OFF);
		led_state.led1 = LED_OFF;
	}
	else
	{
	 hal_led_control(LED1,LED_ON);
		led_state.led1 = LED_ON;
	}
	if(led_state.led2 == LED_ON)
	{
	 hal_led_control(LED2,LED_OFF);
		led_state.led2 = LED_OFF;
	}
	else
	{
	 hal_led_control(LED2,LED_ON);
		led_state.led2 = LED_ON;
	}
 
}



