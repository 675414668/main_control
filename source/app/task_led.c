#include "task_led.h"

#ifdef CHIP_STM32F103C8T6
static void task_led_test(void *pvParameters);

static void task_led_test(void *pvParameters)
{
   while(1)
	 {
		 hal_led_test_on();
		 osal_msleep(1000);
		 hal_led_test_off();
		 osal_msleep(1000);
	 }

}
#elif CHIP_GD32F130C8T6
void task_led_test(void)
{
	hal_led_test_on();
	hal_delay_ms(1000);
	hal_led_test_off();
	hal_delay_ms(1000);
}
#endif

void task_led_init(void)
{
	hal_led_init();
	
	#ifdef CHIP_STM32F103C8T6
	osal_task_creats(task_led_test,NULL,130,1);
  #elif CHIP_GD32F130C8T6
  #endif
}
