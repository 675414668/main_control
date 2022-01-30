#ifndef __OSAL_SEM_H
#define __OSAL_SEM_H



typedef unsigned int osal_sem_t;

int osal_sem_create(osal_sem_t * sem);
int osal_sem_delete(osal_sem_t *sem);
int osal_sem_post(osal_sem_t *sem);
int osal_sem_post_from_isr(osal_sem_t *sem);
int osal_sem_wait(osal_sem_t *sem);
int osal_sem_wait_from_isr(osal_sem_t *sem);
int osal_sem_wait_timeout(osal_sem_t *sem,int msec);

#endif 

