#include "lcd.h"

enum 
{
	KEY_NULL=0,
	KEY1_S,
	KEY1_L,
	KEY2_S,
	KEY2_L,
	KEY3_S,
	KEY3_L,
};

typedef  struct 
{
	uint16_t key1_count;
	uint16_t key2_count;
	uint16_t key3_count;
	uint16_t press;
}key_crl_t;
key_crl_t key_crl;

typedef struct 
{
	uint16_t gif_timecount;
	uint8_t astronaut_image_num;
	uint16_t waiting_count;
	uint8_t waiting_time;
}lcd_tim_ctrl_t;
lcd_tim_ctrl_t lcd_tim_ctrl;

static void bsp_lcd_gpio_init(void);
static void bsp_lcd_driver_init(void);
static void bsp_key_gpio_init(void);
static void bsp_key_tim_init(void);
static void bsp_key_scan(void);
static void lcd_astronaut_image_change(void);
static void lcd_waiting_time_change(void);

void bsp_lcd_init(void)
{
	bsp_lcd_gpio_init();//初始化GPIO
	bsp_lcd_driver_init();
}

void bsp_key_init(void)
{
	bsp_key_gpio_init();
	bsp_key_tim_init();
	lcd_tim_ctrl.astronaut_image_num=1;
	lcd_tim_ctrl.gif_timecount=0;
	lcd_tim_ctrl.waiting_time=1;
}

void bsp_lcd_gpio_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(LCD_CONTROL_RCU, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LCD_CONTROL_RES|LCD_CONTROL_DC|LCD_CONTROL_BLK|LCD_CONTROL_CS1|LCD_CONTROL_CS2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(LCD_CONTROL_PORT, &GPIO_InitStructure);//初始化
	GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_RES|LCD_CONTROL_DC|LCD_CONTROL_BLK|LCD_CONTROL_CS1|LCD_CONTROL_CS2);

	GPIO_InitStructure.GPIO_Pin =LCD_CONTROL_SCK|LCD_CONTROL_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(LCD_CONTROL_PORT, &GPIO_InitStructure); 
	GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_SCK|LCD_CONTROL_SDA);

	GPIO_InitStructure.GPIO_Pin = LCD_CONTROL_MISO;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
 	GPIO_Init(LCD_CONTROL_PORT, &GPIO_InitStructure);	  //初始化GPIOE8,10

}


void bsp_lcd_spi_init(void)
{
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(LCD_SPI_RCU, ENABLE);//使能LCD_SPI


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

static void bsp_key_gpio_init(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(KEY_RCC, ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = KEY1_PIN|KEY2_PIN|KEY3_PIN;
  GPIO_Init(KEY_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(KEY_PORT,KEY1_PIN|KEY2_PIN|KEY3_PIN);
}

static void bsp_key_tim_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	
	RCC_APB1PeriphClockCmd(KEY_TIM_RCC,ENABLE);
	
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period = KEY_TIM_PERIOD;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = KEY_TIM_PRESCALER;
	TIM_TimeBaseInit(KEY_TIM,&TIM_TimeBaseInitTypeStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_InitTypeStruct.NVIC_IRQChannel = KEY_TIM_IRQN;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	TIM_Cmd(KEY_TIM,ENABLE);
}	

static void bsp_lcd_driver_init(void)
{
		LCD_RES_RESET();//复位
//	bsp_delay_ms(100);
	LCD_RES_SET();
//	bsp_delay_ms(100);
	
	LCD_BLK_SET();//打开背光
//  bsp_delay_ms(100);
	
	//************* Start Initial Sequence **********//
	bsp_lcd_write_reg(0x11); //Sleep out 
//	bsp_delay_ms(120);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	bsp_lcd_write_reg(0x36);
	if(USE_HORIZONTAL==0)bsp_lcd_write_8bit(0x00);
	else if(USE_HORIZONTAL==1)bsp_lcd_write_8bit(0xC0);
	else if(USE_HORIZONTAL==2)bsp_lcd_write_8bit(0x70);
	else bsp_lcd_write_8bit(0xA0);

	bsp_lcd_write_reg(0x3A);			
	bsp_lcd_write_8bit(0x05);

	bsp_lcd_write_reg(0xB2);			
	bsp_lcd_write_8bit(0x0C);
	bsp_lcd_write_8bit(0x0C); 
	bsp_lcd_write_8bit(0x00); 
	bsp_lcd_write_8bit(0x33); 
	bsp_lcd_write_8bit(0x33); 			

	bsp_lcd_write_reg(0xB7);			
	bsp_lcd_write_8bit(0x35);

	bsp_lcd_write_reg(0xBB);			
	bsp_lcd_write_8bit(0x32); //Vcom=1.35V
					
	bsp_lcd_write_reg(0xC2);
	bsp_lcd_write_8bit(0x01);

	bsp_lcd_write_reg(0xC3);			
	bsp_lcd_write_8bit(0x15); //GVDD=4.8V  颜色深度
				
	bsp_lcd_write_reg(0xC4);			
	bsp_lcd_write_8bit(0x20); //VDV, 0x20:0v

	bsp_lcd_write_reg(0xC6);			
	bsp_lcd_write_8bit(0x0F); //0x0F:60Hz        	

	bsp_lcd_write_reg(0xD0);			
	bsp_lcd_write_8bit(0xA4);
	bsp_lcd_write_8bit(0xA1); 

	bsp_lcd_write_reg(0xE0);
	bsp_lcd_write_8bit(0xD0);   
	bsp_lcd_write_8bit(0x08);   
	bsp_lcd_write_8bit(0x0E);   
	bsp_lcd_write_8bit(0x09);   
	bsp_lcd_write_8bit(0x09);   
	bsp_lcd_write_8bit(0x05);   
	bsp_lcd_write_8bit(0x31);   
	bsp_lcd_write_8bit(0x33);   
	bsp_lcd_write_8bit(0x48);   
	bsp_lcd_write_8bit(0x17);   
	bsp_lcd_write_8bit(0x14);   
	bsp_lcd_write_8bit(0x15);   
	bsp_lcd_write_8bit(0x31);   
	bsp_lcd_write_8bit(0x34);   

	bsp_lcd_write_reg(0xE1);     
	bsp_lcd_write_8bit(0xD0);   
	bsp_lcd_write_8bit(0x08);   
	bsp_lcd_write_8bit(0x0E);   
	bsp_lcd_write_8bit(0x09);   
	bsp_lcd_write_8bit(0x09);   
	bsp_lcd_write_8bit(0x15);   
	bsp_lcd_write_8bit(0x31);   
	bsp_lcd_write_8bit(0x33);   
	bsp_lcd_write_8bit(0x48);   
	bsp_lcd_write_8bit(0x17);   
	bsp_lcd_write_8bit(0x14);   
	bsp_lcd_write_8bit(0x15);   
	bsp_lcd_write_8bit(0x31);   
	bsp_lcd_write_8bit(0x34);
	bsp_lcd_write_reg(0x21); 

	bsp_lcd_write_reg(0x29);
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void bsp_lcd_write_bus(uint8_t dat) 
{	
	u8 i;
	LCD_CS1_RESET();
	for(i=0;i<8;i++)
	{			  
		LCD_SCK_RESET();
		if(dat&0x80)
		{
		   LCD_SDA_SET();
		}
		else
		{
		   LCD_SDA_RESET();
		}
		LCD_SCK_SET();
		dat<<=1;
	}	
  LCD_CS1_SET();	
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void bsp_lcd_write_8bit(uint8_t dat)
{
	bsp_lcd_write_bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void bsp_lcd_write_16bit(uint16_t dat)
{
	bsp_lcd_write_bus(dat>>8);
	bsp_lcd_write_bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void bsp_lcd_write_reg(uint8_t dat)
{
	LCD_DC_RESET();//写命令
	bsp_lcd_write_bus(dat);
	LCD_DC_SET();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void bsp_lcd_set_addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		bsp_lcd_write_reg(0x2a);//列地址设置
		bsp_lcd_write_16bit(x1);
		bsp_lcd_write_16bit(x2);
		bsp_lcd_write_reg(0x2b);//行地址设置
		bsp_lcd_write_16bit(y1+0x14);
		bsp_lcd_write_16bit(y2+0x14);
		bsp_lcd_write_reg(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		bsp_lcd_write_reg(0x2a);//列地址设置
		bsp_lcd_write_16bit(x1);
		bsp_lcd_write_16bit(x2);
		bsp_lcd_write_reg(0x2b);//行地址设置
		bsp_lcd_write_16bit(y1+0x14);
		bsp_lcd_write_16bit(y2+0x14);
		bsp_lcd_write_reg(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		bsp_lcd_write_reg(0x2a);//列地址设置
		bsp_lcd_write_16bit(x1+0x14);
		bsp_lcd_write_16bit(x2+0x14);
		bsp_lcd_write_reg(0x2b);//行地址设置
		bsp_lcd_write_16bit(y1);
		bsp_lcd_write_16bit(y2);
		bsp_lcd_write_reg(0x2c);//储存器写
	}
	else
	{
		bsp_lcd_write_reg(0x2a);//列地址设置
		bsp_lcd_write_16bit(x1+0x14);
		bsp_lcd_write_16bit(x2+0x14);
		bsp_lcd_write_reg(0x2b);//行地址设置
		bsp_lcd_write_16bit(y1);
		bsp_lcd_write_16bit(y2);
		bsp_lcd_write_reg(0x2c);//储存器写
	}
} 

static void bsp_key_scan(void)
{
	if(GPIO_ReadInputDataBit(KEY_PORT,KEY1_PIN)==0)
	{
		key_crl.key1_count++;
		if(key_crl.key1_count>KEY_L_TIM)  key_crl.press = KEY1_L;
	}
	else
	{
		if(key_crl.key1_count<KEY_L_TIM && key_crl.key1_count>KEY_S_TIM)       key_crl.press = KEY1_S;
		else if(key_crl.key1_count>KEY_L_TIM)  key_crl.press = KEY1_L;
		key_crl.key1_count=0;
	}
	if(GPIO_ReadInputDataBit(KEY_PORT,KEY2_PIN)==0)
	{
		key_crl.key2_count++;
		if(key_crl.key2_count>KEY_L_TIM)  key_crl.press = KEY2_L;
	}
	else
	{
		if(key_crl.key2_count<KEY_L_TIM && key_crl.key2_count>KEY_S_TIM)       key_crl.press = KEY2_S;
		else if(key_crl.key2_count>KEY_L_TIM)  key_crl.press = KEY2_L;
		key_crl.key2_count=0;
	}
	if(GPIO_ReadInputDataBit(KEY_PORT,KEY3_PIN)==0)
	{
		key_crl.key3_count++;
		if(key_crl.key3_count>KEY_L_TIM)  key_crl.press = KEY3_L;
	}
	else
	{
		if(key_crl.key3_count<KEY_L_TIM && key_crl.key3_count>KEY_S_TIM)       key_crl.press = KEY3_S;
		else if(key_crl.key3_count>KEY_L_TIM)  key_crl.press = KEY3_L;
		key_crl.key3_count=0;
	}
}

uint8_t bsp_get_key_press(void)
{
	return key_crl.press;
}

void bsp_set_key_press(uint8_t state)
{
	key_crl.press=state;
}

static void lcd_astronaut_image_change(void)
{
	if(lcd_tim_ctrl.gif_timecount==ASTRONAUT_IMAGE_TIM)
	{
		lcd_tim_ctrl.gif_timecount=1;
	}
	else
	{
		lcd_tim_ctrl.gif_timecount++;
	}
	if((lcd_tim_ctrl.gif_timecount%ASTRONAUT_IMAGE_SPEED)==0)
	{
		if(lcd_tim_ctrl.astronaut_image_num==ASTRONAUT_IMAGE_NUM)
		{
			lcd_tim_ctrl.astronaut_image_num=1;
		}
		else
		{
			lcd_tim_ctrl.astronaut_image_num++;
		}
	}
}
static void lcd_waiting_time_change(void)
{
	if(lcd_tim_ctrl.waiting_count==WAITING_TIM)
	{
		lcd_tim_ctrl.waiting_count=1;
	}
	else
	{
		lcd_tim_ctrl.waiting_count++;
	}
	if((lcd_tim_ctrl.waiting_count%WAITING_SPEED)==0)
	{
		if(lcd_tim_ctrl.waiting_time==WAITING_NUM)
		{
			lcd_tim_ctrl.waiting_time=1;
		}
		else
		{
			lcd_tim_ctrl.waiting_time++;
		}
	}
}
uint8_t bsp_lcd_get_astronaut_image_num(void)
{
	return lcd_tim_ctrl.astronaut_image_num;
}
uint8_t bsp_lcd_get_waiting_time(void)
{
	return lcd_tim_ctrl.waiting_time;
}
void KEY_TIM_IRQHANDLER(void)
{
	if(TIM_GetITStatus(KEY_TIM,TIM_IT_Update)==SET)
	{
		bsp_key_scan();
		lcd_astronaut_image_change();
		lcd_waiting_time_change();
		TIM_ClearITPendingBit(KEY_TIM,TIM_IT_Update);
	}
}




