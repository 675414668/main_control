#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

#define TIM_PWM           TIM3
#define TIM_PWM_PORT      GPIOA
#define TIM_PWM_PIN       GPIO_Pin_6
#define TIM_PWM_PERIOD    (1000)//周期时间 1000*1us=1ms
#define TIM_PWM_PRE_VAL   (72 - 1)//定时器预分频器设置最大值0xff，72M/(72-1+1)=1us
#define TIM_PWM_PULSE     (1000/3)//高电平占比
void bsp_timer_init(void);
void bsp_tim_pwm_enable(void);
void bsp_tim_pwm_disable(void);
void bsp_tim_pwm_pulse_adjust(uint32_t pwm_pulse);
#endif 


