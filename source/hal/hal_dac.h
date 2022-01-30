#ifndef __HAL_DAC_H
#define __HAL_DAC_H

#include "dac.h"

void hal_dac_init(void);
void hal_dac_enable(uint32_t DAC_Channel);
void hal_dac_disable(uint32_t DAC_Channel);
void hal_dac_set_channel1_data(uint32_t DAC_Align, uint16_t Data);
void hal_dac_software_trigger_enable(uint32_t DAC_Channel);
void hal_dac_software_trigger_disable(uint32_t DAC_Channel);
#endif 


