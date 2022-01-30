#ifndef __TIMER_H
#define __TIMER_H
#include "gd32f1x0.h"
#include "usart.h"

#define TIM_SYS_PRESCALER   71
#define TIM_SYS_PERIOD      999   //72M/((71+1)*(999+1))=1000us=1ms

#define TIM_STOPWATCH_PRESCALER   71
#define TIM_STOPWATCH_PERIOD      999   //72M/((71+1)*(999+1))=1000us=1ms

#define TIM_USART_PRESCALER   71
#define TIM_USART_PERIOD      999   //72M/((71+1)*(999+1))=1000us=1ms

#define TIM_WAIT   100

void bsp_timer_init(void);
uint8_t bsp_get_usart_rx_over_flag(void);
void bsp_clear_usart_rx_over_flag(void);
void bsp_get_sys_time_buff(uint8_t *data);
void bsp_get_stopwatch_time_buff(uint8_t *data);

#endif 
