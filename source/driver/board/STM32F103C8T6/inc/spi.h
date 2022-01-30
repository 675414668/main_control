#ifndef __SPI_H
#define __SPI_H			  	 
#include "stm32f10x.h"
#include "string.h"   

#define LCD_SPI               SPI1
#define LCD_SPI_RCU           RCC_APB2Periph_SPI1

#define LCD_SPI_GPIO_RCU      RCC_APB2Periph_GPIOA
#define LCD_SPI_GPIO_PORT     GPIOA
#define LCD_SPI_SCK_PIN       GPIO_Pin_5
#define LCD_SPI_MISO_PIN      GPIO_Pin_6
#define LCD_SPI_MOSI_PIN      GPIO_Pin_7

void bsp_lcd_spi_init(void);
uint8_t bsp_lcd_spi_rw_byte(uint8_t TxData);
void bsp_lcd_spi_transfer_8bit(void);
void bsp_lcd_spi_transfer_16bit(void);
void bsp_lcd_spi_enable(void);
void bsp_lcd_spi_dma_enable(void);
#endif

