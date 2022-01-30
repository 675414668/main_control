#ifndef __TASK_LED_H
#define __TASK_LED_H

#include "hal_led.h"

#ifdef CHIP_STM32F103C8T6
#include "osal.h"

#elif CHIP_GD32F130C8T6
#include "hal_delay.h"

void task_led_test(void);
#endif

void task_led_init(void);

#endif 
