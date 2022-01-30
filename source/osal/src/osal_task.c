#include "FreeRTOS.h"
#include "task.h"
#include "osal_task.h"

int osal_task_creats(void* task, void* const param, const uint16_t stack_depth, uint16_t priority)
{
	return (int)xTaskCreate((TaskFunction_t)task,
		                        "task",
	                          stack_depth,
	                          param,
	                          (UBaseType_t)priority,
	                           NULL);
}

void osal_task_scheduler_start(void)
{
	vTaskStartScheduler();
}
