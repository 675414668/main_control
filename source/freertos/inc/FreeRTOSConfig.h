#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
extern uint32_t SystemCoreClock;

#define configUSE_PREEMPTION		          1 //1使用抢占式内核，0使用协程
#define configUSE_IDLE_HOOK			          0 //1，使用空闲钩子；0，不使用
#define configUSE_TICK_HOOK			          0 //1，使用时间片钩子；0，不使用
#define configCPU_CLOCK_HZ			         ( ( unsigned long ) SystemCoreClock ) //CPU频率
#define configTICK_RATE_HZ			         ( ( TickType_t ) 1000 ) //时钟节拍频率，这里设置为1000，周期就是1ms
#define configMAX_PRIORITIES		         ( 5 ) //可使用的最大优先级
#define configMINIMAL_STACK_SIZE	       ( ( unsigned short ) 130 ) //空闲任务使用的堆栈大小
#define configTOTAL_HEAP_SIZE		         ( ( size_t ) ( 6 * 1024 ) ) //系统所有总的堆大小
#define configMAX_TASK_NAME_LEN		       ( 10 ) //任务名字字符串长度
#define configUSE_TRACE_FACILITY	        0 //为1启用可视化跟踪调试
#define configUSE_16_BIT_TICKS		        0 //系统节拍计数器变量数据类型
#define configIDLE_SHOULD_YIELD		        1 //为1时空闲任务放弃CPU使用权给其他同优先级的用户任务
#define configUSE_MUTEXES                 1
#define configQUEUE_REGISTRY_SIZE         5 //设置注册的信号量和消息量个数
#define configCHECK_FOR_STACK_OVERFLOW    0 //堆栈溢出检测,设置值1,2
#define configUSE_RECURSIVE_MUTEXES       1 //设置成1表示使用递归互斥量,设置成0表示不使用
#define configUSE_MALLOC_FAILED_HOOK      0 //1使用内存申请失败钩子函数
#define configUSE_APPLICATION_TASK_TAG    0 //为任务分配标签值，设置为1来使用vTaskSetApplicationTaskTag函数，分配的标签只对应用程序有用，内核不使用
#define configUSE_COUNTING_SEMAPHORES     1 //为1时使用计数信号量
#define configGENERATE_RUN_TIME_STATS     0 //为1,则该函数将总运行时间写入*pulTotalRunTime中
#define configUSE_CO_ROUTINES 		        0 //为1时启用协程，启用协程以后必须添加文件croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES   ( 2 ) //协程的有效优先级数目

#define configKERNEL_INTERRUPT_PRIORITY 		    255 //用来设置RTOS内核自己的中断优先级
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	  191 //配置系统内核优先级
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15  //配置系统内核优先级,这里使用的是4bit优先级,所以最低为15,跟1 中的配置相同
 //FreeRTOS可选函数配置选项 
#define INCLUDE_xTaskGetSchedulerState          1                       
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_uxTaskGetStackHighWaterMark     1

#define xPortPendSVHandler  PendSV_Handler
#define vPortSVCHandler     SVC_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

