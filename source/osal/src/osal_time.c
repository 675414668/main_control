#include "FreeRTOS.h"
#include "task.h"
#include "osal_time.h"

void osal_msleep(uint16_t millisecond)
{
	vTaskDelay(pdMS_TO_TICKS(millisecond));
}


