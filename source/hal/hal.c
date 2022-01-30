#include "hal.h"

void hal_init(void)
{
	#ifdef CHIP_STM32F130C8T6
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
  #elif  CHIP_GD32F130C8T6
	//nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
  #endif
	hal_delay_init();
}
