#include "hal_dac.h"

void hal_dac_init(void)
{
  bsp_dac_init();
}

void hal_dac_enable(uint32_t DAC_Channel)
{
	 bsp_dac_enable(DAC_Channel);
}

void hal_dac_disable(uint32_t DAC_Channel)
{
	 bsp_dac_disable(DAC_Channel);
}

void hal_dac_set_channel1_data(uint32_t DAC_Align, uint16_t Data)
{
	bsp_dac_set_channel1_data(DAC_Align, Data);
}

void hal_dac_software_trigger_enable(uint32_t DAC_Channel)
{
	bsp_dac_software_trigger_enable(DAC_Channel);
}

void hal_dac_software_trigger_disable(uint32_t DAC_Channel)
{
	bsp_dac_software_trigger_disable(DAC_Channel);
}

