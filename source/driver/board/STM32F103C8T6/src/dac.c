#include "dac.h"

static void bsp_dac_gpio_init(void);
static void bsp_dac_driver_init(void);

void bsp_dac_init(void)
{
	bsp_dac_gpio_init();
	bsp_dac_driver_init();
}

static void bsp_dac_gpio_init(void)
{
	//c8t6ÎÞDAC
}

static void bsp_dac_driver_init(void)
{

}

void bsp_dac_enable(uint32_t DAC_Channel)
{
	 DAC_Cmd(DAC_Channel, ENABLE);
}

void bsp_dac_disable(uint32_t DAC_Channel)
{
	 DAC_Cmd(DAC_Channel, DISABLE);
}

void bsp_dac_set_channel1_data(uint32_t DAC_Align, uint16_t Data)
{
	DAC_SetChannel1Data(DAC_Align, Data);
}

void bsp_dac_software_trigger_enable(uint32_t DAC_Channel)
{
	DAC_SoftwareTriggerCmd(DAC_Channel, ENABLE);
}

void bsp_dac_software_trigger_disable(uint32_t DAC_Channel)
{
	DAC_SoftwareTriggerCmd(DAC_Channel, DISABLE);
}
