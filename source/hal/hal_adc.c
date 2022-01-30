#include "hal_adc.h"

void hal_adc_init(void)
{
   bsp_adc_init();
}

uint32_t hal_read_adc_data(ADC_TypeDef* ADCx)
{
	uint32_t data;
	data=bsp_read_adc_data(ADCx);
	return data;
}


float hal_read_adc_data_voltage(ADC_TypeDef* ADCx)
{
	float data=0;
	data=bsp_read_adc_data_voltage(ADCx);
	return data;
}
