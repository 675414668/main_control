#include "timer.h"

static void bsp_tim_pwm_gpio_init(void);
static void bsp_tim_pwm_driver_init(void);

void bsp_timer_init(void)
{
	bsp_tim_pwm_gpio_init();
	bsp_tim_pwm_driver_init();
}

static void bsp_tim_pwm_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = TIM_PWM_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(TIM_PWM_PORT, &GPIO_InitStructure);
}

static void bsp_tim_pwm_driver_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  TIM_TimeBaseStructure.TIM_Period = TIM_PWM_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_PWM_PRE_VAL;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM_PWM, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_PWM_PULSE;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM_PWM, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM_PWM, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM_PWM, ENABLE);

  /* TIM_PWM enable counter */
}

void bsp_tim_pwm_enable(void)
{
	 TIM_Cmd(TIM_PWM, ENABLE);
}

void bsp_tim_pwm_disable(void)
{
	TIM_Cmd(TIM_PWM, DISABLE);
}

void bsp_tim_pwm_pulse_adjust(uint32_t pwm_pulse)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = pwm_pulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM_PWM, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM_PWM, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM_PWM, ENABLE);
}
