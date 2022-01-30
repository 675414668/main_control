#ifndef __OSAL_TASK_H
#define __OSAL_TASK_H

int osal_task_creats(void* task, void* const param, const uint16_t stack_depth, uint16_t priority);
void osal_task_scheduler_start(void);

#endif 


