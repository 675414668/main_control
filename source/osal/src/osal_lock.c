#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "osal_lock.h"

//int osal_lock_create(osal_lock_t * lock)
//{
//	SemaphoreHandle_t handle = xSemaphoreCreateMutex();
//	*lock = (osal_lock_t)handle
//	return handle?0:-ENOMEM;
//}

//int osal_lock_delete(osal_lock_t * lock)
//{
//	vSemaphoreDelete((SemaphoreHandle_t)(*lock));
//	return 0;
//}

//int osal_lock_lock(osal_lock_t * lock)
//{
//	if(pdPASS == xSemaphoreTake((SemaphoreHandle_t)lock,portMAX_DELAY))
//		return -EPIPE;
//	else
//		return 0;
//}

//int osal_lock_unlock(osal_lock_t * lock)
//{
//	if(pdPASS == xSemaphoreGive((SemaphoreHandle_t)lock))
//		return -EPIPE;
//	else
//		return 0;
//}
