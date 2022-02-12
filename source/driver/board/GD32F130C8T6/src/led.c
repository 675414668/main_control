#include "led.h"

static void bsp_led_gpio_init(void);

void bsp_led_init(void)
{
   bsp_led_gpio_init();
	 bsp_led_control(LED1,LED_OFF);
	 bsp_led_control(LED2,LED_OFF);
}

static void bsp_led_gpio_init(void)
{
    rcu_periph_clock_enable(LED_RCC);//GPIOB时钟打开
    gpio_mode_set(LED_PORT, GPIO_MODE_OUTPUT, GPIO_OSPEED_50MHZ, LED1_PIN|LED2_PIN);//PB4配置成输出
}

uint8_t bsp_led_control(uint8_t led,uint8_t state)
{
	if(led==1 && state==1)
	{
		gpio_bit_set(LED_PORT,LED1_PIN);
		
		return 1;
	}
	else if(led==1 && state==0)
	{
		gpio_bit_reset(LED_PORT,LED1_PIN);
		return 1;
	}
	else if(led==2 && state==1)
	{
		gpio_bit_set(LED_PORT,LED2_PIN);
		return 1;
	}
	else if(led==2 && state==0)
	{
		gpio_bit_reset(LED_PORT,LED2_PIN);
		return 1;
	}
	else
	{
		return 0;
	}
}
