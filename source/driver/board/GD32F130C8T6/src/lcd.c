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

typedef struct 
{
	uint8_t begin;
	uint8_t timebuff[14];
	uint16_t ms;
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
}stopwatch_t;
stopwatch_t stopwatch;

static void bsp_lcd_gpio_init(void);
static void bsp_lcd_driver_init(void);
static void bsp_key_gpio_init(void);
static void bsp_key_tim_init(void);
static void bsp_stopwatch_data_init(void);
static void bsp_key_scan(void);
static void lcd_astronaut_image_change(void);
static void lcd_waiting_time_change(void);
static void bsp_timer_stopwatch(void);

void bsp_lcd_init(void)
{
	bsp_lcd_gpio_init();//初始化GPIO
	bsp_lcd_driver_init();
	bsp_stopwatch_data_init();
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
 	rcu_periph_clock_enable(LCD_CONTROL_RCU);	 //使能A端口时钟

	gpio_mode_set(LCD_CONTROL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,  LCD_CONTROL_RES|LCD_CONTROL_DC|LCD_CONTROL_BLK|LCD_CONTROL_CS1|LCD_CONTROL_CS2);
  gpio_mode_set(LCD_CONTROL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,  LCD_CONTROL_SCK|LCD_CONTROL_SDA);
	gpio_output_options_set(LCD_CONTROL_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, LCD_CONTROL_RES|LCD_CONTROL_DC|LCD_CONTROL_BLK|LCD_CONTROL_CS1|LCD_CONTROL_CS2|LCD_CONTROL_SCK|LCD_CONTROL_SDA);
  gpio_bit_set(LCD_CONTROL_PORT, LCD_CONTROL_RES|LCD_CONTROL_DC|LCD_CONTROL_BLK|LCD_CONTROL_CS1|LCD_CONTROL_CS2|LCD_CONTROL_SCK|LCD_CONTROL_SDA);
  gpio_mode_set(LCD_CONTROL_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,LCD_CONTROL_MISO);
}

static void bsp_key_gpio_init(void)
{
	rcu_periph_clock_enable(KEY_RCC);	 //使能A端口时钟

	gpio_mode_set(LCD_CONTROL_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,KEY1_PIN|KEY2_PIN|KEY3_PIN);

	gpio_bit_reset(KEY_PORT,KEY1_PIN|KEY2_PIN|KEY3_PIN);
}

static void bsp_key_tim_init(void)
{
	timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(KEY_TIM_RCC);

    timer_deinit(KEY_TIM);

    timer_initpara.prescaler         = KEY_TIM_PRESCALER;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = KEY_TIM_PERIOD;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(KEY_TIM,&timer_initpara);

		nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);//1 bit抢占优先级,3 bit子优先级，数值越小，优先级越高
		nvic_irq_enable(KEY_TIM_IRQN, 0, 1);//中断优先级使能
		timer_interrupt_enable(KEY_TIM, TIMER_INT_UP);
	
    timer_auto_reload_shadow_enable(KEY_TIM);//自动重装载影子比较器使能
    timer_enable(KEY_TIM);//使能定时器
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
	uint8_t i;
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
	if(gpio_input_bit_get(KEY_PORT,KEY1_PIN)==0)
	{
		key_crl.key1_count++;
//		if(key_crl.key1_count>KEY_L_TIM)
//		{
//			key_crl.press = KEY1_L;
//			key_crl.key1_count=0;
//		}			
	}
	else
	{
		if(key_crl.key1_count<KEY_L_TIM && key_crl.key1_count>KEY_S_TIM)       key_crl.press = KEY1_S;
		else if(key_crl.key1_count>KEY_L_TIM)  key_crl.press = KEY1_L;
		key_crl.key1_count=0;
	}
	if(gpio_input_bit_get(KEY_PORT,KEY2_PIN)==0)
	{
		key_crl.key2_count++;
//		if(key_crl.key2_count>KEY_L_TIM)  
//		{
//			key_crl.press = KEY2_L;
//			key_crl.key2_count=0;
//		}
	}
	else
	{
		if(key_crl.key2_count<KEY_L_TIM && key_crl.key2_count>KEY_S_TIM)       key_crl.press = KEY2_S;
		else if(key_crl.key2_count>KEY_L_TIM)  key_crl.press = KEY2_L;
		key_crl.key2_count=0;
	}
	if(gpio_input_bit_get(KEY_PORT,KEY3_PIN)==0)
	{
		key_crl.key3_count++;
//		if(key_crl.key3_count>KEY_L_TIM)
//		{
//			key_crl.press = KEY3_L;
//			key_crl.key3_count=0;
//		}			
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
static void bsp_stopwatch_data_init(void)
{
	stopwatch.timebuff[0]=91;
	stopwatch.timebuff[1]=0x30;
	stopwatch.timebuff[2]=0x30;
	stopwatch.timebuff[3]=58;
	stopwatch.timebuff[4]=0x30;
	stopwatch.timebuff[5]=0x30;
	stopwatch.timebuff[6]=58;
	stopwatch.timebuff[7]=0x30;
	stopwatch.timebuff[8]=0x30;
	stopwatch.timebuff[9]=58;
	stopwatch.timebuff[10]=0x30;
	stopwatch.timebuff[11]=0x30;
	stopwatch.timebuff[12]=0x30;
	stopwatch.timebuff[13]=93;
}
static void bsp_timer_stopwatch(void)
{
	if(stopwatch.begin==1)
	{
		stopwatch.ms++;
		if(stopwatch.ms==1000)
		{
			stopwatch.ms=0;
			stopwatch.sec++;
		}
		if(stopwatch.sec==60)
		{
			stopwatch.sec=0;
			stopwatch.min++;
		}
		if(stopwatch.min==60)
		{
			stopwatch.min=0;
			stopwatch.hour++;
		}
		if(stopwatch.hour==24)
		{
			stopwatch.hour=0;
		}
		stopwatch.timebuff[0]=91;
		stopwatch.timebuff[1]=stopwatch.hour/10+0x30;
		stopwatch.timebuff[2]=stopwatch.hour%10+0x30;
		stopwatch.timebuff[3]=58;
		stopwatch.timebuff[4]=stopwatch.min/10+0x30;
		stopwatch.timebuff[5]=stopwatch.min%10+0x30;
		stopwatch.timebuff[6]=58;
		stopwatch.timebuff[7]=stopwatch.sec/10+0x30;
		stopwatch.timebuff[8]=stopwatch.sec%10+0x30;
		stopwatch.timebuff[9]=58;
		stopwatch.timebuff[10]=stopwatch.ms/100+0x30;
		stopwatch.timebuff[11]=(stopwatch.ms/10)%10+0x30;
		stopwatch.timebuff[12]=stopwatch.ms%10+0x30;
		stopwatch.timebuff[13]=93;
	}
}

void bsp_get_stopwatch_timebuff(uint8_t *data)
{
	memcpy(data,stopwatch.timebuff,14);
}
void bsp_stopwatch_timebuff_clear(void)
{
	bsp_stopwatch_data_init();
}
void bsp_stopwatch_ctrl(uint8_t state)
{
	stopwatch.begin=state;
}

void KEY_TIM_IRQHANDLER(void)
{
	if(timer_interrupt_flag_get(KEY_TIM,TIMER_INT_FLAG_UP)==SET)
	{
		bsp_key_scan();
		lcd_astronaut_image_change();
		lcd_waiting_time_change();
		bsp_timer_stopwatch();
		timer_interrupt_flag_clear(KEY_TIM,TIMER_INT_FLAG_UP);
	}
}






