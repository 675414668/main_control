#ifndef __OSAL_LOCK_H
#define __OSAL_LOCK_H

typedef unsigned int osal_lock_t;

int osal_lock_create(osal_lock_t * lock);
int osal_lock_delete(osal_lock_t * lock);
int osal_lock_lock(osal_lock_t * lock);
int osal_lock_unlock(osal_lock_t * lock);

#endif 

