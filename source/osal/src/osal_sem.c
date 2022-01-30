//#include "FreeRTOS.h"
//#include "task.h"
//#include "semphr.h"
//#include "osal_sem.h"

//int osal_sem_create(osal_sem_t * sem)
//{
//	SemaphoreHandle_t handle = xSemaphoreCreateBinary();
//	*sem = (osal_sem_t)handle
//	return handle?0:-ENOMEM;
//}

//int osal_sem_delete(osal_sem_t *sem)
//{
//	vSemaphoreDelete((SemaphoreHandle_t)(*sem));
//	return 0;
//}

//int osal_sem_post(osal_sem_t *sem)
//{
//	if(pdPASS == xSemaphoreGive((SemaphoreHandle_t)sem))
//		return -EPIPE;
//	else
//		return 0;
//}

//int osal_sem_post_from_isr(osal_sem_t *sem)
//{
//	if(pdPASS == xSemaphoreGiveFromISR((SemaphoreHandle_t)sem,NULL))
//		return -EPIPE;
//	else
//		return 0;
//}

//int osal_sem_wait(osal_sem_t *sem)
//{
//	if(pdPASS == xSemaphoreTake((SemaphoreHandle_t)sem,portMAX_DELAY))
//		return -EPIPE;
//	else
//		return 0;
//}

//int osal_sem_wait_from_isr(osal_sem_t *sem)
//{
//	if(pdPASS == xSemaphoreTakeFromISR((SemaphoreHandle_t)sem,NULL))
//		return -EPIPE;
//	else
//		return 0;
//}

//int osal_sem_wait_timeout(osal_sem_t *sem,int msec)
//{
//	if(pdPASS == xSemaphoreTake((SemaphoreHandle_t)sem,pdMS_TO_TICKS(msec)))
//		return -EPIPE;
//	else
//		return 0;
//}
