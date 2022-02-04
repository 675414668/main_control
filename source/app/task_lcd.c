#include "task_lcd.h"
#include "hal_usart.h"
#include "pic.h"

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

enum
{
	LCD_DISPLAY_INIT=0,
	LCD_DISPLAY_ASTRONAUT,
	LCD_DISPLAY_MENU,
	LCD_DISPLAY_LASER_CTRL,
};

typedef struct 
{
	uint8_t state;
	uint8_t real_state;
	uint8_t astronaut_num;
	uint8_t point_num;
}lcd_display_t;
lcd_display_t lcd_display;

typedef  struct
{
	uint8_t up_down;
}key_ctrl_t;
key_ctrl_t key_ctrl;

static void lcd_data_init(void);
static void lcd_show_init(void);
static void lcd_waiting_point(void);
static void lcd_show_astronaut(void);
static void lcd_show_menu(void);
static void lcd_show_cursor(uint8_t x,uint8_t y,uint8_t key_num);
static void lcd_show_laser_control(void);

static void key_null(void);
static void key1_short(void);
static void key1_long(void);
static void key2_short(void);
static void key2_long(void);
static void key3_short(void);
static void key3_long(void);
static void key_default(void);

void task_lcd_init(void)
{
	hal_lcd_init();
	hal_key_init();
	lcd_data_init();
	hal_lcd_fill(0,0,280,240,BLACK);
}

static void lcd_data_init(void)
{
	lcd_display.state=LCD_DISPLAY_INIT;
	lcd_display.real_state=LCD_DISPLAY_INIT;
}
void task_lcd_display(void)
{
	switch(lcd_display.state)
	{
		case LCD_DISPLAY_INIT:      { lcd_show_init();          break ;}
		case LCD_DISPLAY_ASTRONAUT: { lcd_show_astronaut();     break ;}
		case LCD_DISPLAY_MENU:      { lcd_show_menu();          break ;}
		case LCD_DISPLAY_LASER_CTRL:{ lcd_show_laser_control();          break ;}
		default: {break;}
			
	}
}

void task_key_scan(void)
{
	switch(hal_get_key_press())
	{
		case KEY_NULL:{ key_null();      break;};
		case KEY1_S:  { key1_short();    break;};
		case KEY1_L:  { key1_long();     break;};
		case KEY2_S:  { key2_short();    break;};
		case KEY2_L:  { key2_long();     break;};
		case KEY3_S:  { key3_short();    break;};
		case KEY3_L:  { key3_long();     break;};
		default :     { key_default();   break;};
	}
}

static void lcd_show_init(void)
{
	hal_lcd_fill(0,0,280,145,BLACK);
	hal_lcd_show_string(30,0,(uint8_t *)"system begin",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,16,(uint8_t *)"system clock set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,32,(uint8_t *)"cpu frequency:84M HZ",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,48,(uint8_t *)"usart set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,64,(uint8_t *)"usaer1 baudrate:115200",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,80,(uint8_t *)"led set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,96,(uint8_t *)"keyboard set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,112,(uint8_t *)"hardware version:V1.0.0",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,128,(uint8_t *)"software version:V1.0.0",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,180,(uint8_t *)"Loading",BRRED,BLACK,32,0);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void lcd_waiting_point(void)
{
	lcd_display.point_num=hal_lcd_get_waiting_point();
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		switch (lcd_display.point_num)
		{
			case 1:{hal_lcd_show_string(145,180,(uint8_t *)"   ",BRRED,BLACK,32,0); break;}
			case 2:{hal_lcd_show_string(145,180,(uint8_t *)".  ",BRRED,BLACK,32,0); break;}
			case 3:{hal_lcd_show_string(145,180,(uint8_t *)".. ",BRRED,BLACK,32,0); break;}
			case 4:{hal_lcd_show_string(145,180,(uint8_t *)"...",BRRED,BLACK,32,0); break;}
			default:{break;}
		}
		lcd_display.point_num=0;
	}
}

static void lcd_show_astronaut(void)
{
	lcd_display.astronaut_num=hal_lcd_get_astronaut_image_num();
	switch (lcd_display.astronaut_num)
	{
		case 1:{hal_lcd_show_picture(235,200,45,38,gImage_0); break;}
		case 2:{hal_lcd_show_picture(235,200,45,38,gImage_1); break;}
		case 3:{hal_lcd_show_picture(235,200,45,38,gImage_2); break;}
		case 4:{hal_lcd_show_picture(235,200,45,38,gImage_3); break;}
		case 5:{hal_lcd_show_picture(235,200,45,38,gImage_4); break;}
		case 6:{hal_lcd_show_picture(235,200,45,38,gImage_5); break;}
		case 7:{hal_lcd_show_picture(235,200,45,38,gImage_6); break;}
		case 8:{hal_lcd_show_picture(235,200,45,38,gImage_7); break;}
		case 9:{hal_lcd_show_picture(235,200,45,38,gImage_8); break;}
		case 10:{hal_lcd_show_picture(235,200,45,38,gImage_9); break;}
		case 11:{hal_lcd_show_picture(235,200,45,38,gImage_10); break;}
		case 12:{hal_lcd_show_picture(235,200,45,38,gImage_11); break;}
		case 13:{hal_lcd_show_picture(235,200,45,38,gImage_12); break;}
		case 14:{hal_lcd_show_picture(235,200,45,38,gImage_13); break;}
		default:{break;}
	}
	lcd_waiting_point();
	lcd_display.astronaut_num=0;
}

static void lcd_show_menu(void)
{
	hal_lcd_show_string(116,0,(uint8_t *)"MENU",BRRED,BLACK,24,0);
	hal_lcd_show_string(50,24,(uint8_t *)"laser control",BRRED,BLACK,16,0);
	hal_lcd_show_string(50,40,(uint8_t *)"RGB led control",BRRED,BLACK,16,0);
	hal_lcd_show_string(50,56,(uint8_t *)"stopwatch",BRRED,BLACK,16,0);
	hal_lcd_show_string(50,72,(uint8_t *)"WiFi connection",BRRED,BLACK,16,0);
	hal_lcd_show_string(50,88,(uint8_t *)"game",BRRED,BLACK,16,0);
	hal_lcd_show_string(50,104,(uint8_t *)"system set up",BRRED,BLACK,16,0);
	lcd_show_cursor(30,24,key_ctrl.up_down);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}
static void lcd_show_cursor(uint8_t x,uint8_t y,uint8_t key_num)
{
	hal_lcd_fill(30,24,46,24+16*MENU_OPTIONS_NUM,BLACK);
	hal_lcd_show_string(x,y+key_num*16,(uint8_t *)"->",BRRED,BLACK,16,0);
}
static void lcd_show_laser_control(void)
{
	hal_lcd_show_string(62,0,(uint8_t *)"LASER CONTROL",BRRED,BLACK,24,0);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void key_null(void)
{
	
}

static void key1_short(void)
{
	if(lcd_display.state==LCD_DISPLAY_ASTRONAUT)
	{
		if(lcd_display.real_state==LCD_DISPLAY_INIT)
		{
			lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_MENU;
		  hal_lcd_fill(0,0,280,240,BLACK);
		}
		else if(lcd_display.real_state==LCD_DISPLAY_MENU)
		{
			if(key_ctrl.up_down<(MENU_OPTIONS_NUM-1)) key_ctrl.up_down++;
			else key_ctrl.up_down=0;
			lcd_display.state=LCD_DISPLAY_MENU;
		}
	}
	
	hal_set_key_press(KEY_NULL);
}

static void key1_long(void)
{

}

static void key2_short(void)
{
	if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(0,0,280,240,BLACK);
	}
}

static void key2_long(void)
{

}

static void key3_short(void)
{
	if(lcd_display.real_state==LCD_DISPLAY_MENU && key_ctrl.up_down==0)
	{
		lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
		hal_lcd_fill(0,0,280,240,BLACK);
	}
}

static void key3_long(void)
{

}

static void key_default(void)
{
	
}

