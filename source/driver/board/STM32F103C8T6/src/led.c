#include "led.h"

#define LED_TEST_PORT GPIOC
#define LED_TEST_PIN  GPIO_Pin_13

static void bsp_led_gpio_init(void);

void bsp_led_init(void)
{
   bsp_led_gpio_init();
	 bsp_led_test_off();
}

static void bsp_led_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LED_TEST_PIN;                                             
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                         
	GPIO_Init(LED_TEST_PORT, &GPIO_InitStructure); 
}

void bsp_led_test_on(void)
{
	GPIO_SetBits(LED_TEST_PORT,LED_TEST_PIN);
}

void bsp_led_test_off(void)
{
	GPIO_ResetBits(LED_TEST_PORT,LED_TEST_PIN);
}
