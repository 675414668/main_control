#ifndef __DMA_H
#define	__DMA_H	   

#include "gd32f1x0.h"
#include "string.h"	    
#include "spi.h"	 

#define LCD_DMA_RCU      RCU_DMA
#define LCD_DMA_CHANNEL  DMA_CH2


void bsp_lcd_dma_picture_init(uint32_t cmar,uint16_t cndtr);//≈‰÷√DMA1_CHx
void bsp_lcd_dma_fill_init(uint32_t cmar,uint16_t cndtr);
void bsp_lcd_dma_enable(void);// πƒ‹DMA1_CHx
void bsp_lcd_dma_transfer_finished(void);
		   
#endif



