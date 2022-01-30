#ifndef __DAC_H
#define __DAC_H

#include "stm32f10x.h"

#define DAC_CH1           DAC_Channel_1
#define DAC_CH1_PORT      GPIOA
#define DAC_CH1_PIN       GPIO_Pin_4


void bsp_dac_init(void);
void bsp_dac_enable(uint32_t DAC_Channel);
void bsp_dac_disable(uint32_t DAC_Channel);
void bsp_dac_set_channel1_data(uint32_t DAC_Align, uint16_t Data);
void bsp_dac_software_trigger_enable(uint32_t DAC_Channel);
void bsp_dac_software_trigger_disable(uint32_t DAC_Channel);
#endif 


