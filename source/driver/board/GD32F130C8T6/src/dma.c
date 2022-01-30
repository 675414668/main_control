#include "dma.h"

uint16_t lcd_dma_mem_len;//����DMAÿ�����ݴ��͵ĳ��� 	    
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//LCD_DMA_CHANNEL:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ����� 
void bsp_lcd_dma_picture_init(uint32_t cmar,uint16_t cndtr)
{
	dma_parameter_struct dma_init_struct;
	
	rcu_periph_clock_enable(LCD_DMA_RCU);
	
  dma_deinit(LCD_DMA_CHANNEL);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	lcd_dma_mem_len=cndtr;
	dma_init_struct.periph_addr = (uint32_t )&SPI_DATA(LCD_SPI);  //DMA����ADC����ַ
	dma_init_struct.memory_addr = cmar;  //DMA�ڴ����ַ
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	dma_init_struct.number = cndtr;  //DMAͨ����DMA����Ĵ�С
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;  //�����ַ�Ĵ�������
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;  //�ڴ��ַ�Ĵ�������
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;  //���ݿ��Ϊ8λ
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT; //���ݿ��Ϊ8λ
	//dma_init_struct.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	dma_init_struct.priority = DMA_PRIORITY_MEDIUM; //DMAͨ�� xӵ�������ȼ� 
	dma_memory_to_memory_disable(LCD_DMA_CHANNEL);
	dma_init(LCD_DMA_CHANNEL, dma_init_struct);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
	  	
} 

void bsp_lcd_dma_fill_init(uint32_t cmar,uint16_t cndtr)
{
	dma_parameter_struct dma_init_struct;
	
 	rcu_periph_clock_enable(LCD_DMA_RCU);
	
  dma_deinit(LCD_DMA_CHANNEL);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	lcd_dma_mem_len=cndtr;
	dma_init_struct.periph_addr = (uint32_t )&SPI_DATA(LCD_SPI);  //DMA����ADC����ַ
	dma_init_struct.memory_addr = cmar;  //DMA�ڴ����ַ
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	dma_init_struct.number = cndtr;  //DMAͨ����DMA����Ĵ�С
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;  //�����ַ�Ĵ�������
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_DISABLE;  //�ڴ��ַ�Ĵ�������
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;  //���ݿ��Ϊ16λ
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_16BIT; //���ݿ��Ϊ16λ
	//dma_init_struct.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	dma_init_struct.priority = DMA_PRIORITY_MEDIUM; //DMAͨ�� xӵ�������ȼ� 
	dma_memory_to_memory_disable(LCD_DMA_CHANNEL);
	dma_init(LCD_DMA_CHANNEL, dma_init_struct);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
} 

//����һ��DMA����
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
 

























