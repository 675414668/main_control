#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

#define ADC_FOR_PWM                  ADC1
#define ADC_FOR_PWM_CH               ADC_Channel_1
#define ADC_FOR_PWM_CLK_DIV          RCC_PCLK2_Div8
#define ADC_FOR_PWM_SAMOLE_TIME      ADC_SampleTime_1Cycles5

#define ADC_FOR_PWM_GPIO_PORT         GPIOA
#define ADC_FOR_PWM_GPIO_PIN          GPIO_Pin_1  

void bsp_adc_init(void);
uint32_t bsp_read_adc_data(ADC_TypeDef* ADCx);
float bsp_read_adc_data_voltage(ADC_TypeDef* ADCx);

#endif 


