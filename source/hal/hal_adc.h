#ifndef __HAL_ADC_H
#define __HAL_ADC_H

#include "adc.h"

void hal_adc_init(void);
uint32_t hal_read_adc_data(ADC_TypeDef* ADCx);
float hal_read_adc_data_voltage(ADC_TypeDef* ADCx);
#endif 


