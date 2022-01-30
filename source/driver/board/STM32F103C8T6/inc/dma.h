#ifndef __DMA_H
#define	__DMA_H	   

#include "stm32f10x.h"
#include "string.h"	    
#include "stm32f10x_dma.h"		

#define LCD_DMA_RCU      RCC_AHBPeriph_DMA1
#define LCD_DMA_CHANNEL  DMA1_Channel3


void bsp_lcd_dma_picture_init(uint32_t cmar,uint16_t cndtr);//≈‰÷√DMA1_CHx
void bsp_lcd_dma_fill_init(uint32_t cmar,uint16_t cndtr);
void bsp_lcd_dma_enable(void);// πƒ‹DMA1_CHx
void bsp_lcd_dma_transfer_finished(void);
		   
#endif



