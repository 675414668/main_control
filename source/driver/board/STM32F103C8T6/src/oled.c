#include "oled.h"

#include "oledfont.h"  	//字库
static void bsp_oled_gpio_init(void);
static void bsp_oled_driver_init(void);

static void bsp_oled_d0_set(void);
static void bsp_oled_d0_reset(void);
static void bsp_oled_d1_set(void);
static void bsp_oled_d1_reset(void);
static void bsp_oled_dc_set(void);
static void bsp_oled_dc_reset(void);
static void bsp_oled_res_set(void);
//static void bsp_oled_res_reset(void);

void bsp_oled_init(void)
{
	bsp_oled_gpio_init();
	bsp_oled_driver_init();
}

static void bsp_oled_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = OLED_D0_Pin|OLED_D1_Pin|OLED_RES_Pin|OLED_DC_Pin;                                             
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                         
	GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStructure); 
}
static void bsp_oled_driver_init(void)
{ 	
  bsp_oled_res_set();
//	osal_msleep(100);
//	bsp_oled_res_reset();
//	osal_msleep(100);
//	bsp_oled_res_set(); 
					  
	bsp_oled_write_byte(0xAE,OLED_CMD);//--turn off oled panel
	bsp_oled_write_byte(0x00,OLED_CMD);//---set low column address
	bsp_oled_write_byte(0x10,OLED_CMD);//---set high column address
	bsp_oled_write_byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	bsp_oled_write_byte(0x81,OLED_CMD);//--set contrast control register
	bsp_oled_write_byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	bsp_oled_write_byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	bsp_oled_write_byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	bsp_oled_write_byte(0xA6,OLED_CMD);//--set normal display
	bsp_oled_write_byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	bsp_oled_write_byte(0x3f,OLED_CMD);//--1/64 duty
	bsp_oled_write_byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	bsp_oled_write_byte(0x00,OLED_CMD);//-not offset
	bsp_oled_write_byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	bsp_oled_write_byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	bsp_oled_write_byte(0xD9,OLED_CMD);//--set pre-charge period
	bsp_oled_write_byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	bsp_oled_write_byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	bsp_oled_write_byte(0x12,OLED_CMD);
	bsp_oled_write_byte(0xDB,OLED_CMD);//--set vcomh
	bsp_oled_write_byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	bsp_oled_write_byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	bsp_oled_write_byte(0x02,OLED_CMD);//
	bsp_oled_write_byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	bsp_oled_write_byte(0x14,OLED_CMD);//--set(0x10) disable
	bsp_oled_write_byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	bsp_oled_write_byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	bsp_oled_write_byte(0xAF,OLED_CMD);//--turn on oled panel
	
	bsp_oled_write_byte(0xAF,OLED_CMD); /*display ON*/ 
	bsp_oled_clear();
	bsp_oled_set_pos(0,0); 	
}  

static void bsp_oled_d0_set(void)
{
	GPIO_SetBits(OLED_D0_PORT,OLED_D0_Pin);
}	

static void bsp_oled_d0_reset(void)
{
	GPIO_ResetBits(OLED_D0_PORT,OLED_D0_Pin);
}	

static void bsp_oled_d1_set(void)
{
	GPIO_SetBits(OLED_D1_PORT,OLED_D1_Pin);
}	

static void bsp_oled_d1_reset(void)
{
	GPIO_ResetBits(OLED_D1_PORT,OLED_D1_Pin);
}	

static void bsp_oled_res_set(void)
{
	GPIO_SetBits(OLED_RES_PORT,OLED_RES_Pin);
}	

//static void bsp_oled_res_reset(void)
//{
//	GPIO_ResetBits(OLED_RES_PORT,OLED_RES_Pin);
//}	

static void bsp_oled_dc_set(void)
{
	GPIO_SetBits(OLED_DC_PORT,OLED_DC_Pin);
}	

static void bsp_oled_dc_reset(void)
{
	GPIO_ResetBits(OLED_DC_PORT,OLED_DC_Pin);
}	

void bsp_oled_write_byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;			  
	if(cmd)
	  bsp_oled_dc_set();
	else 
	  bsp_oled_dc_reset();		  
	for(i=0;i<8;i++)
	{			  
		bsp_oled_d0_reset();
		if(dat&0x80)
		   bsp_oled_d1_set();
		else 
		   bsp_oled_d1_reset();
		bsp_oled_d0_set();
		dat<<=1;   
	}				 		  
	bsp_oled_dc_set();   	  
} 


void bsp_oled_set_pos(unsigned char x, unsigned char y) 
{ 
	bsp_oled_write_byte(0xb0+y,OLED_CMD);
	bsp_oled_write_byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	bsp_oled_write_byte((x&0x0f)|0x01,OLED_CMD); 
}   

void bsp_oled_display_on(void)
{
	bsp_oled_write_byte(0X8D,OLED_CMD);  //SET DCDC命令
	bsp_oled_write_byte(0X14,OLED_CMD);  //DCDC ON
	bsp_oled_write_byte(0XAF,OLED_CMD);  //DISPLAY ON
}

void bsp_oled_display_off(void)
{
	bsp_oled_write_byte(0X8D,OLED_CMD);  //SET DCDC命令
	bsp_oled_write_byte(0X10,OLED_CMD);  //DCDC OFF
	bsp_oled_write_byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
void bsp_oled_clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		bsp_oled_write_byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		bsp_oled_write_byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		bsp_oled_write_byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)bsp_oled_write_byte(0,OLED_DATA); 
	}																		 //更新显示
}

//在指定位置显示一个字符,包括部分字符x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
void bsp_oled_show_char(uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';														//得到偏移后的值			
	if(x>Max_Column-1)
	{
		x=x;
		y=y+2;
	}
	if(SIZE==16)
	{
		bsp_oled_set_pos(x,y);	
		for(i=0;i<8;i++)
		bsp_oled_write_byte(D8X16[c*16+i],OLED_DATA);
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<8;i++)
		bsp_oled_write_byte(D8X16[c*16+i+8],OLED_DATA);
	}
	else if(SIZE==12)
	{	
		bsp_oled_set_pos(x,y);	
		for(i=0;i<6;i++)
		bsp_oled_write_byte(D12X12[c][i],OLED_DATA);
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<6;i++)
		bsp_oled_write_byte(D12X12[c][i+6],OLED_DATA);
	}
	else if(SIZE==24)
	{	
		bsp_oled_set_pos(x,y);	
		for(i=0;i<12;i++)
		bsp_oled_write_byte(D24X24[c][i],OLED_DATA);
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<12;i++)
		bsp_oled_write_byte(D24X24[c][i+12],OLED_DATA);
	}
	else if(SIZE==8)
	{
		
		bsp_oled_set_pos(x,y);
		for(i=0;i<8;i++)
		{
			bsp_oled_write_byte(D8X8[c][i],OLED_DATA);
		}
	}
	else if(SIZE==6)
	{
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<6;i++)
		{
			bsp_oled_write_byte(D6X8[c][i],OLED_DATA);
		}
	}
}

//在指定位置显示一个字符,可调节字符大小 x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
void bsp_oled_show_char_adjust(uint8_t size,uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';														//得到偏移后的值			
	if(x>Max_Column-1)
	{
		x=x-127;
		y=y+2;
	}
	if(size==24)
	{	
		bsp_oled_set_pos(x,y);	
		for(i=0;i<12;i++)
		bsp_oled_write_byte(D24X24[c][i],OLED_DATA);
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<12;i++)
		bsp_oled_write_byte(D24X24[c][i+12],OLED_DATA);
	}
	else if(size==16)
	{
		bsp_oled_set_pos(x,y);	
		for(i=0;i<8;i++)
		bsp_oled_write_byte(D8X16[c*16+i],OLED_DATA);
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<8;i++)
		bsp_oled_write_byte(D8X16[c*16+i+8],OLED_DATA);
	}
	else if(size==12)
	{	
		bsp_oled_set_pos(x,y);	
		for(i=0;i<6;i++)
		bsp_oled_write_byte(D12X12[c][i],OLED_DATA);
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<6;i++)
		bsp_oled_write_byte(D12X12[c][i+6],OLED_DATA);
	}
	else if(size==8)
	{
		
		bsp_oled_set_pos(x,y);
		for(i=0;i<8;i++)
		{
			bsp_oled_write_byte(D8X8[c][i],OLED_DATA);
		}
	}
	else if(size==6)
	{
		bsp_oled_set_pos(x,y+1);
		for(i=0;i<6;i++)
		{
			bsp_oled_write_byte(D6X8[c][i],OLED_DATA);
		}
	}
}

//m^n函数
uint32_t bsp_oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}		

/**
  * @brief 显示2个数字
	* @param x,y :起点坐标
	*				 len :数字的位数，即显示几位有效数字
  *				 size:字体大小
  *				 mode:模式	0,填充模式;1,叠加模式
  *        num:数值(0~4294967295);
	* @retval None
  */ 		  
void bsp_oled_show_num(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/bsp_oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				bsp_oled_show_char(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	bsp_oled_show_char(x+(size/2)*t,y,temp+'0'); 
	}
} 

//显示一个字符号串
void bsp_oled_show_string(uint8_t x,uint8_t y,char *chr)
{
	unsigned char j=0;
	while(chr[j]!='\0')
	{		bsp_oled_show_char(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

  
