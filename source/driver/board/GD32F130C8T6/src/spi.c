#include "spi.h"


void bsp_lcd_spi_init(void)
{
	spi_parameter_struct spi_init_struct;

	rcu_periph_clock_enable(LCD_SPI_RCU);//使能LCD_SPI
	rcu_periph_clock_enable(LCD_SPI_GPIO_RCU);//使能LCD_SPI_GPIO_PORT


  gpio_af_set(GPIOA, GPIO_AF_0, LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
  gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
  gpio_bit_set(GPIOA,LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);
	
	spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;//全双工模式
	spi_init_struct.device_mode = SPI_MASTER;//设置SPI工作模式：主机模式
	spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;//设置SPI数据大小：8位帧结构
	spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;//串行同步时钟空闲时SCLK位高电平
	                                                               //串行同步时钟空第二个时钟沿捕获
	spi_init_struct.nss = SPI_NSS_SOFT;//NSS信号由软件管理
	spi_init_struct.prescale = SPI_PSC_4;//波特率预分频值：波特率预分频值为4
	//spi_init_struct.SPI_CRCPolynomial = 7;//CRC值计算的多项式
	spi_init_struct.endian = SPI_ENDIAN_MSB;
	spi_init(LCD_SPI,&spi_init_struct);//初始化SPI
	spi_enable(LCD_SPI);//使能SPI
}



//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
uint8_t bsp_lcd_spi_rw_byte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TBE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	spi_i2s_data_transmit(LCD_SPI, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (spi_i2s_flag_get(LCD_SPI, I2S_FLAG_RBNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return spi_i2s_data_receive(LCD_SPI); //返回通过SPIx最近接收的数据					    
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
