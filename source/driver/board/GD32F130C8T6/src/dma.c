#include "dma.h"

uint16_t lcd_dma_mem_len;//保存DMA每次数据传送的长度 	    
//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//LCD_DMA_CHANNEL:DMA通道CHx
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量 
void bsp_lcd_dma_picture_init(uint32_t cmar,uint16_t cndtr)
{
	dma_parameter_struct dma_init_struct;
	
	rcu_periph_clock_enable(LCD_DMA_RCU);
	
  dma_deinit(LCD_DMA_CHANNEL);   //将DMA的通道1寄存器重设为缺省值
	lcd_dma_mem_len=cndtr;
	dma_init_struct.periph_addr = (uint32_t )&SPI_DATA(LCD_SPI);  //DMA外设ADC基地址
	dma_init_struct.memory_addr = cmar;  //DMA内存基地址
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;  //数据传输方向，从内存读取发送到外设
	dma_init_struct.number = cndtr;  //DMA通道的DMA缓存的大小
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;  //外设地址寄存器不变
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;  //内存地址寄存器递增
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;  //数据宽度为8位
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT; //数据宽度为8位
	//dma_init_struct.DMA_Mode = DMA_Mode_Normal;  //工作在正常缓存模式
	dma_init_struct.priority = DMA_PRIORITY_MEDIUM; //DMA通道 x拥有中优先级 
	dma_memory_to_memory_disable(LCD_DMA_CHANNEL);
	dma_init(LCD_DMA_CHANNEL, dma_init_struct);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
	  	
} 

void bsp_lcd_dma_fill_init(uint32_t cmar,uint16_t cndtr)
{
	dma_parameter_struct dma_init_struct;
	
 	rcu_periph_clock_enable(LCD_DMA_RCU);
	
  dma_deinit(LCD_DMA_CHANNEL);   //将DMA的通道1寄存器重设为缺省值
	lcd_dma_mem_len=cndtr;
	dma_init_struct.periph_addr = (uint32_t )&SPI_DATA(LCD_SPI);  //DMA外设ADC基地址
	dma_init_struct.memory_addr = cmar;  //DMA内存基地址
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;  //数据传输方向，从内存读取发送到外设
	dma_init_struct.number = cndtr;  //DMA通道的DMA缓存的大小
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;  //外设地址寄存器不变
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_DISABLE;  //内存地址寄存器不变
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;  //数据宽度为16位
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_16BIT; //数据宽度为16位
	//dma_init_struct.DMA_Mode = DMA_Mode_Normal;  //工作在正常缓存模式
	dma_init_struct.priority = DMA_PRIORITY_MEDIUM; //DMA通道 x拥有中优先级 
	dma_memory_to_memory_disable(LCD_DMA_CHANNEL);
	dma_init(LCD_DMA_CHANNEL, dma_init_struct);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
} 

//开启一次DMA传输
void bsp_lcd_dma_enable(void)
{ 
	dma_channel_disable(LCD_DMA_CHANNEL);
 	dma_transfer_number_config(LCD_DMA_CHANNEL,lcd_dma_mem_len);
 	dma_channel_enable(LCD_DMA_CHANNEL);
}	  
void bsp_lcd_dma_transfer_finished(void)
{
	while(1)
	{
	  if(dma_flag_get(LCD_DMA_CHANNEL,DMA_FLAG_FTF)!=RESET)
    {
		  dma_flag_clear(LCD_DMA_CHANNEL,DMA_FLAG_FTF);
		  break; 
	  }
	}
}
 

























