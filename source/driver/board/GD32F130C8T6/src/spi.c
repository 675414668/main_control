#include "spi.h"


void bsp_lcd_spi_init(void)
{
	spi_parameter_struct spi_init_struct;

	rcu_periph_clock_enable(LCD_SPI_RCU);//ʹ��LCD_SPI
	rcu_periph_clock_enable(LCD_SPI_GPIO_RCU);//ʹ��LCD_SPI_GPIO_PORT


  gpio_af_set(GPIOA, GPIO_AF_0, LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
  gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
  gpio_bit_set(GPIOA,LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
	
	spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;//ȫ˫��ģʽ
	spi_init_struct.device_mode = SPI_MASTER;//����SPI����ģʽ������ģʽ
	spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;//����SPI���ݴ�С��8λ֡�ṹ
	spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;//����ͬ��ʱ�ӿ���ʱSCLKλ�ߵ�ƽ
	                                                               //����ͬ��ʱ�ӿյڶ���ʱ���ز���
	spi_init_struct.nss = SPI_NSS_SOFT;//NSS�ź����������
	spi_init_struct.prescale = SPI_PSC_4;//������Ԥ��Ƶֵ��������Ԥ��ƵֵΪ4
	//spi_init_struct.SPI_CRCPolynomial = 7;//CRCֵ����Ķ���ʽ
	spi_init_struct.endian = SPI_ENDIAN_MSB;
	spi_init(LCD_SPI,&spi_init_struct);//��ʼ��SPI
	spi_enable(LCD_SPI);//ʹ��SPI
}



//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
uint8_t bsp_lcd_spi_rw_byte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TBE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	spi_i2s_data_transmit(LCD_SPI, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (spi_i2s_flag_get(LCD_SPI, I2S_FLAG_RBNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return spi_i2s_data_receive(LCD_SPI); //����ͨ��SPIx������յ�����					    
}

void bsp_lcd_spi_transfer_8bit(void)
{
	spi_i2s_data_frame_format_config(LCD_SPI,SPI_FRAMESIZE_8BIT);
}
void bsp_lcd_spi_transfer_16bit(void)
{
   spi_i2s_data_frame_format_config(LCD_SPI,SPI_FRAMESIZE_16BIT);
}
void bsp_lcd_spi_enable(void)
{
	spi_enable(LCD_SPI);
}

void bsp_lcd_spi_dma_enable(void)
{
	spi_dma_enable(LCD_SPI,SPI_DMA_TRANSMIT);
}
