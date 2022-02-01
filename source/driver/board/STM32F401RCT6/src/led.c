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
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(LED_RCC, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = LED1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

uint8_t bsp_led_control(uint8_t led,uint8_t state)
{
	if(led==1 && state==1)
	{
		GPIO_SetBits(LED_PORT,LED1_PIN);
		return 1;
	}
	else if(led==1 && state==0)
	{
		GPIO_ResetBits(LED_PORT,LED1_PIN);
		return 1;
	}
	else if(led==2 && state==1)
	{
		GPIO_SetBits(LED_PORT,LED2_PIN);
		return 1;
	}
	else if(led==2 && state==0)
	{
		GPIO_ResetBits(LED_PORT,LED2_PIN);
		return 1;
	}
	else
	{
		return 0;
	}
}
