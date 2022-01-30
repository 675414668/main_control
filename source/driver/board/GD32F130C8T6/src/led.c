#include "led.h"

#define LED_TEST_RCU  RCU_GPIOB
#define LED_TEST_PORT GPIOB
#define LED_TEST_PIN  GPIO_PIN_4

static void bsp_led_gpio_init(void);

void bsp_led_init(void)
{
   bsp_led_gpio_init();
	 bsp_led_test_off();
}

static void bsp_led_gpio_init(void)
{
    rcu_periph_clock_enable(LED_TEST_RCU);//GPIOB时钟打开
    gpio_mode_set(LED_TEST_PORT, GPIO_MODE_OUTPUT, GPIO_OSPEED_50MHZ, LED_TEST_PIN);//PB4配置成输出
}

void bsp_led_test_on(void)
{
	gpio_bit_set(LED_TEST_PORT,LED_TEST_PIN);
}

void bsp_led_test_off(void)
{
	gpio_bit_reset(LED_TEST_PORT,LED_TEST_PIN);
}
