#include "spi.h"



void bsp_lcd_spi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(LCD_SPI_RCU, ENABLE);//使能LCD_SPI
	RCC_APB2PeriphClockCmd(LCD_SPI_GPIO_RCU, ENABLE);//使能LCD_SPI_GPIO_PORT

	GPIO_InitStructure.GPIO_Pin =LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //复用推挽输出
	GPIO_Init(LCD_SPI_GPIO_PORT, &GPIO_InitStructure); //初始化LCD_SPI_GPIO_PORT
	GPIO_SetBits(LCD_SPI_GPIO_PORT,LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//全双工模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//设置SPI工作模式：主机模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//设置SPI数据大小：8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//串行同步时钟空闲时SCLK位高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//串行同步时钟空第二个时钟沿捕获
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS信号由软件管理
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//波特率预分频值：波特率预分频值为4
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//数据传输高位先行
	SPI_InitStructure.SPI_CRCPolynomial = 7;//CRC值计算的多项式
	SPI_Init(LCD_SPI,&SPI_InitStructure);//初始化SPI
	SPI_Cmd(LCD_SPI, ENABLE);//使能SPI
}



//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
uint8_t bsp_lcd_spi_rw_byte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(LCD_SPI, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(LCD_SPI); //返回通过SPIx最近接收的数据					    
}

void bsp_lcd_spi_transfer_8bit(void)
{
	SPI_DataSizeConfig(LCD_SPI,SPI_DataSize_8b);
}
void bsp_lcd_spi_transfer_16bit(void)
{
   SPI_DataSizeConfig(LCD_SPI,SPI_DataSize_16b);
}
void bsp_lcd_spi_enable(void)
{
	SPI_Cmd(LCD_SPI, ENABLE);//使能SPI
}

void bsp_lcd_spi_dma_enable(void)
{
	SPI_I2S_DMACmd(LCD_SPI,SPI_I2S_DMAReq_Tx,ENABLE);
}
