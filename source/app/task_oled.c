#include "task_oled.h"
#include "bmp.h"//Í¼¿â
#include "FreeRTOS.h"
#include "task.h"

uint8_t task_oled_stack = 0;

static void task_oled_display(void *pvParameters);

void task_oled_init(void)
{
	hal_oled_init();
	osal_task_creats(task_oled_display,NULL,1062,1);
}

static void task_oled_display(void *pvParameters)
{
   while(1)
	 {
      	hal_oled_clear();
	      hal_oled_show_string(8, 0, "RTOS Loading.");
	      hal_oled_draw_bmp(40,2,88,8,logo);
	      osal_msleep(1000);
	      hal_oled_show_string(8, 0, "RTOS Loading..");
	      osal_msleep(1000);
        hal_oled_show_string(8, 0, "RTOS Loading...");
	      osal_msleep(1000);
		    task_oled_stack=uxTaskGetStackHighWaterMark(NULL);
	 }

}


