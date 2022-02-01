#include "sys_clk.h"

RCC_ClocksTypeDef get_rcc_clock; 

uint8_t bsp_sys_clk_init(void)
{
	  RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);

    if(RCC_WaitForHSEStartUp() == SUCCESS)
    {
 			  RCC_PLLConfig(RCC_PLLSource_HSE, PLL_M, PLL_N, PLL_P, PLL_Q);     
        
        RCC_PLLCmd(ENABLE); 
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);    
       
        while(RCC_GetSYSCLKSource() != 0x08);    

        RCC_HCLKConfig(HCLK_CONFIG);                          
        RCC_PCLK1Config(PCLK1_CONFIG);                           
        RCC_PCLK2Config(PCLK2_CONFIG);
			
				RCC_GetClocksFreq(&get_rcc_clock);
			
			  if(get_rcc_clock.SYSCLK_Frequency == SYSCLK_TARGET_FRE 
					&& get_rcc_clock.HCLK_Frequency == HCLK_TARGET_FRE 
				  && get_rcc_clock.PCLK1_Frequency == PCLK1_TARGET_FRE
				  && get_rcc_clock.PCLK2_Frequency == PCLK2_TARGET_FRE)
				{
					 return SUCCESS;
				}
				else
				{
					return ERROR;
				}
       			
    }
		else
		{
			return ERROR;
		}
}

uint32_t bsp_get_clock_frequency(uint8_t clk)
{
	if(clk == SYSCLK_FREQUENCY)
	{
		return get_rcc_clock.SYSCLK_Frequency;
	}
	else if(clk == HCLK_FREQUENCY)
	{
		return get_rcc_clock.HCLK_Frequency;
	}
	else if(clk == PCLK1_FREQUENCY)
	{
		return get_rcc_clock.PCLK1_Frequency;
	}
	else if(clk == PCLK2_FREQUENCY)
	{
		return get_rcc_clock.PCLK2_Frequency;
	}
	else
	{
		return ERROR;
	}
}
