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
	LCD_DISPLAY_LASER_CTRL_SET,
	LCD_DISPLAY_SYSTEM,
	LCD_DISPLAY_SYSTEM_SET,
};

typedef struct 
{
	uint8_t state;
	uint8_t real_state;
	uint8_t astronaut_num;
	uint8_t point_num;
	uint8_t laser_set;//1 mode 2 state
	uint8_t system_set;//1 language 
	uint8_t language_value;
}lcd_display_t;
lcd_display_t lcd_display;

typedef  struct
{
	uint8_t up_down;
}key_ctrl_t;
key_ctrl_t key_ctrl;

typedef  struct
{
	uint8_t mode_value;
	uint8_t state_value;
}laser_ctrl_t;
laser_ctrl_t laser_ctrl;

static void lcd_data_init(void);
static void lcd_show_init(void);
//static void lcd_waiting_point(void);
static void lcd_press_any_key_to_continuet(void);
static void lcd_show_astronaut(void);
static void lcd_show_menu(void);
static void lcd_show_cursor(uint8_t x,uint8_t y,uint8_t key_num);
static void lcd_show_laser_control(void);
static void lcd_show_laser_control_set(void);
static void lcd_show_system(void);
static void lcd_show_system_set(void);

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
	hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
}

static void lcd_data_init(void)
{
	lcd_display.state=LCD_DISPLAY_INIT;
	lcd_display.real_state=LCD_DISPLAY_INIT;
	lcd_display.language_value=1;

}
void task_lcd_display(void)
{
	switch(lcd_display.state)
	{
		case LCD_DISPLAY_INIT:          { lcd_show_init();              break ;}
		case LCD_DISPLAY_ASTRONAUT:     { lcd_show_astronaut();         break ;}
		case LCD_DISPLAY_MENU:          { lcd_show_menu();              break ;}
		case LCD_DISPLAY_LASER_CTRL:    { lcd_show_laser_control();     break ;}
		case LCD_DISPLAY_LASER_CTRL_SET:{ lcd_show_laser_control_set(); break ;}
		case LCD_DISPLAY_SYSTEM:        { lcd_show_system();            break ;}
		case LCD_DISPLAY_SYSTEM_SET:    { lcd_show_system_set();        break ;}
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
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y,(uint8_t *)"system begin",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,(uint8_t *)"system clock init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)"mcu type:stm32f401rct6",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)"mcu frequency:84M HZ",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+4*SHOW_WORD_SIZE,(uint8_t *)"usart init baudrate:115200",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+5*SHOW_WORD_SIZE,(uint8_t *)"lcd init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+6*SHOW_WORD_SIZE,(uint8_t *)"keyboard init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+7*SHOW_WORD_SIZE,(uint8_t *)"laser init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+8*SHOW_WORD_SIZE,(uint8_t *)"user data init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+9*SHOW_WORD_SIZE,(uint8_t *)"hardware version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+10*SHOW_WORD_SIZE,(uint8_t *)"software version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
	}
	else if(lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y,SHOW_WORD_SIZE,(uint8_t *)"系统开启",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"系统时钟初始化完毕",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"芯片型号",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)":stm32f401rct6",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"运行频率",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)":84M HZ",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+4*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"串口波特率",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE,SHOW_WORD_Y+4*SHOW_WORD_SIZE,(uint8_t *)":115200",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+5*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"屏幕初始化完毕",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+6*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"键盘初始化完毕",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+7*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"激光初始化完毕",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+8*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"用户数据初始化完毕",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+9*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"硬件版本号",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE,SHOW_WORD_Y+9*SHOW_WORD_SIZE,(uint8_t *)":V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+10*SHOW_WORD_SIZE,SHOW_WORD_SIZE,(uint8_t *)"软件版本号",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE,SHOW_WORD_Y+10*SHOW_WORD_SIZE,(uint8_t *)":V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
	}

	//hal_lcd_show_string(30,180,(uint8_t *)"Loading",BRRED,BLACK,32,0);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

//static void lcd_waiting_point(void)
//{
//	lcd_display.point_num=hal_lcd_get_waiting_point();
//	if(lcd_display.real_state==LCD_DISPLAY_INIT)
//	{
//		switch (lcd_display.point_num)
//		{
//			case 1:{hal_lcd_show_string(145,180,(uint8_t *)"   ",BRRED,BLACK,32,0); break;}
//			case 2:{hal_lcd_show_string(145,180,(uint8_t *)".  ",BRRED,BLACK,32,0); break;}
//			case 3:{hal_lcd_show_string(145,180,(uint8_t *)".. ",BRRED,BLACK,32,0); break;}
//			case 4:{hal_lcd_show_string(145,180,(uint8_t *)"...",BRRED,BLACK,32,0); break;}
//			default:{break;}
//		}
//		lcd_display.point_num=0;
//	}
//}

static void lcd_press_any_key_to_continuet(void)
{
	lcd_display.point_num=hal_lcd_get_waiting_time();
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		if(lcd_display.language_value==0)
		{
			switch (lcd_display.point_num)
			{
				case 1:{hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y,(uint8_t *)"press any key",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,(uint8_t *)"to continue",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); break;}
				case 2:{hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y,(uint8_t *)"press any key",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,(uint8_t *)"to continue",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); break;}
				case 3:{hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y,(uint8_t *)"             ",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,(uint8_t *)"           ",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE);break;}
				default:{break;}
			}
		}
		else if(lcd_display.language_value==1)
		{
			switch (lcd_display.point_num)
			{
				case 1:{hal_lcd_font_GB2312_string(PRESS_KEY_X,PRESS_KEY_Y,PRESS_KEY_SIZE,(uint8_t *)"按压任意按键",BRRED,BLACK); hal_lcd_font_GB2312_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,PRESS_KEY_SIZE,(uint8_t *)"继续",BRRED,BLACK); break;}
				case 2:{hal_lcd_font_GB2312_string(PRESS_KEY_X,PRESS_KEY_Y,PRESS_KEY_SIZE,(uint8_t *)"按压任意按键",BRRED,BLACK); hal_lcd_font_GB2312_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,PRESS_KEY_SIZE,(uint8_t *)"继续",BRRED,BLACK); break;}
				case 3:{hal_lcd_fill(PRESS_KEY_X,PRESS_KEY_Y,PRESS_KEY_X+PRESS_KEY_SIZE*6,PRESS_KEY_Y+PRESS_KEY_SIZE*2,BLACK);break;}
				default:{break;}
			}
		}

		lcd_display.point_num=0;
	}
}
static void lcd_show_astronaut(void)
{
	lcd_display.astronaut_num=hal_lcd_get_astronaut_image_num();
	switch (lcd_display.astronaut_num)
	{
		case 1: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_0); break;}
		case 2: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_1); break;}
		case 3: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_2); break;}
		case 4: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_3); break;}
		case 5: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_4); break;}
		case 6: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_5); break;}
		case 7: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_6); break;}
		case 8: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_7); break;}
		case 9: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_8); break;}
		case 10:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_9); break;}
		case 11:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_10); break;}
		case 12:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_11); break;}
		case 13:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_12); break;}
		case 14:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_13); break;}
		default:{break;}
	}
	lcd_press_any_key_to_continuet();
	lcd_display.astronaut_num=0;
}

static void lcd_show_menu(void)
{
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(MENU_TITLE_X,MENU_TITLE_Y,(uint8_t *)"MENU",BRRED,BLACK,TITLE_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y,(uint8_t *)"laser control",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,(uint8_t *)"rgb led control",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,(uint8_t *)"stopwatch",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+3*MAIN_WORD_SIZE,(uint8_t *)"wifi connection",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+4*MAIN_WORD_SIZE,(uint8_t *)"game",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+5*MAIN_WORD_SIZE,(uint8_t *)"system set",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
	}
	else if(lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(MENU_TITLE_X,MENU_TITLE_Y,TITLE_SIZE,(uint8_t *)"菜单",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y,MAIN_WORD_SIZE,(uint8_t *)"激光控制",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,MAIN_WORD_SIZE,(uint8_t *)"氛围灯控制",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,MAIN_WORD_SIZE,(uint8_t *)"秒表",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+3*MAIN_WORD_SIZE,MAIN_WORD_SIZE,(uint8_t *)"无线连接",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+4*MAIN_WORD_SIZE,MAIN_WORD_SIZE,(uint8_t *)"游戏",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+5*MAIN_WORD_SIZE,MAIN_WORD_SIZE,(uint8_t *)"系统设置",BRRED,BLACK);
	}
	
	lcd_show_cursor(CURSOR_X,CURSOR_Y,key_ctrl.up_down);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}
static void lcd_show_cursor(uint8_t x,uint8_t y,uint8_t key_num)
{
	if(lcd_display.real_state==LCD_DISPLAY_MENU)
	{
		hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*MENU_OPTIONS_NUM,BLACK);
	  hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
	{
		hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);
	  hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
	{
		if(lcd_display.laser_set==1)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_MODE_SET_NUM,BLACK);
	    hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
		}
		else if(lcd_display.laser_set==2)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_STATE_SET_NUM,BLACK);
	    hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
	{
		hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_SYSTEM_NUM,BLACK);
	  hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
	{
		if(lcd_display.system_set==1)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_LANGUAGE_SET_NUM,BLACK);
	    hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
		}
//		else if(lcd_display.system_set==2)
//		{
//			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_STATE_SET_NUM,BLACK);
//	    hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
//		}
	}

}
static void lcd_show_laser_control(void)
{
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(LASER_CTRL_TITLE_X,LASER_CTRL_TITLE_Y,(uint8_t *)"LASER CONTROL",BRRED,BLACK,TITLE_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y,(uint8_t *)"mode:",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,(uint8_t *)"state:",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		if(laser_ctrl.mode_value==0)      hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y,(uint8_t *)"single",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		else if(laser_ctrl.mode_value==1) hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y,(uint8_t *)"auto  ",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		if(laser_ctrl.state_value==0)      hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,(uint8_t *)"close",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		else if(laser_ctrl.state_value==1) hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,(uint8_t *)"open ",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	}
	else if (lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(LASER_CTRL_TITLE_X,LASER_CTRL_TITLE_Y,TITLE_SIZE,(uint8_t *)"激光控制",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y,BELONG_WORD_SIZE,(uint8_t *)"模式:",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,BELONG_WORD_SIZE,(uint8_t *)"状态:",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,BELONG_WORD_SIZE,(uint8_t *)"离开",BRRED,BLACK);
		if(laser_ctrl.mode_value==0)      hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_SIZE,(uint8_t *)"单发",BRRED,BLACK);
		else if(laser_ctrl.mode_value==1) hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_SIZE,(uint8_t *)"自动  ",BRRED,BLACK);
		if(laser_ctrl.state_value==0)      hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,BELONG_WORD_SIZE,(uint8_t *)"关闭",BRRED,BLACK);
		else if(laser_ctrl.state_value==1) hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,BELONG_WORD_SIZE,(uint8_t *)"开启 ",BRRED,BLACK);

	}

	lcd_show_cursor(CURSOR_X,CURSOR_Y,key_ctrl.up_down);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void lcd_show_laser_control_set(void)
{
	if(lcd_display.language_value==0)
	{
		if(lcd_display.laser_set==1) //set mode
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_show_string(230,37,(uint8_t *)"mode",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"single",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,(uint8_t *)"auto",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
		else if(lcd_display.laser_set==2) //set state
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_show_string(208,37,(uint8_t *)"state",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"close",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,(uint8_t *)"open",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}
	else if (lcd_display.language_value==1)
	{
		if(lcd_display.laser_set==1) //set mode
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_font_GB2312_string(230,37,SET_WORD_SIZE,(uint8_t *)"模式",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y,SET_WORD_SIZE,(uint8_t *)"单发",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,SET_WORD_SIZE,(uint8_t *)"自动",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,SET_WORD_SIZE,(uint8_t *)"离开",BRRED,BLACK);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
		else if(lcd_display.laser_set==2) //set state
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_font_GB2312_string(208,37,SET_WORD_SIZE,(uint8_t *)"状态",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y,SET_WORD_SIZE,(uint8_t *)"关闭",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,SET_WORD_SIZE,(uint8_t *)"打开",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,SET_WORD_SIZE,(uint8_t *)"离开",BRRED,BLACK);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}

}

static void lcd_show_system(void)
{
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(SYSTEM_SET_TITLE_X,SYSTEM_SET_TITLE_Y,(uint8_t *)"SYSTEM SET",BRRED,BLACK,TITLE_SIZE,COVER_MODE);
   	hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y,(uint8_t *)"language:",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	  hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,(uint8_t *)"about",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	  hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	}
	else if(lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(SYSTEM_SET_TITLE_X,SYSTEM_SET_TITLE_Y,TITLE_SIZE,(uint8_t *)"系统设置",BRRED,BLACK);
   	hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y,BELONG_WORD_SIZE,(uint8_t *)"语言:",BRRED,BLACK);
	  hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,BELONG_WORD_SIZE,(uint8_t *)"关于",BRRED,BLACK);
	  hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,BELONG_WORD_SIZE,(uint8_t *)"离开",BRRED,BLACK);
	}
	if(lcd_display.language_value==0)      hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y,(uint8_t *)"English",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	else if(lcd_display.language_value==1) hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_SIZE,(uint8_t *)"简体中文",BRRED,BLACK);
	lcd_show_cursor(CURSOR_X,CURSOR_Y,key_ctrl.up_down);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void lcd_show_system_set(void)
{
	if(lcd_display.language_value==0)
	{
		if(lcd_display.system_set==1) //set language
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_show_string(195,37,(uint8_t *)"language",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"English",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,SET_WORD_SIZE,(uint8_t *)"简体中文",BRRED,BLACK);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}
	else if(lcd_display.language_value==1)
	{
		if(lcd_display.system_set==1) //set language
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_font_GB2312_string(195,37,SET_WORD_SIZE,(uint8_t *)"语言",BRRED,BLACK);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"English",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,SET_WORD_SIZE,(uint8_t *)"简体中文",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,SET_WORD_SIZE,(uint8_t *)"离开",BRRED,BLACK);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}

}

static void key_null(void)
{
	
}

static void key1_short(void)
{
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_MENU)
	{
		if(key_ctrl.up_down<(MENU_OPTIONS_NUM-1)) key_ctrl.up_down++;
		else key_ctrl.up_down=0;
		lcd_display.state=LCD_DISPLAY_MENU;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
	{
		if(key_ctrl.up_down<(LASER_CTRL_OPTIONS_NUM-1)) key_ctrl.up_down++;
		else key_ctrl.up_down=0;
		lcd_display.state=LCD_DISPLAY_LASER_CTRL;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
	{
		if(lcd_display.laser_set==1)
		{
			if(key_ctrl.up_down<(LASER_CTRL_MODE_SET_NUM-1)) key_ctrl.up_down++;
		  else key_ctrl.up_down=0;
		  lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;
		}
		else if(lcd_display.laser_set==2)
		{
			if(key_ctrl.up_down<(LASER_CTRL_STATE_SET_NUM-1)) key_ctrl.up_down++;
		  else key_ctrl.up_down=0;
		  lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
	{
		if(key_ctrl.up_down<(LASER_CTRL_SYSTEM_NUM-1)) key_ctrl.up_down++;
		else key_ctrl.up_down=0;
		lcd_display.state=LCD_DISPLAY_SYSTEM;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
	{
		if(lcd_display.system_set==1)
		{
			if(key_ctrl.up_down<(LASER_CTRL_MODE_SET_NUM-1)) key_ctrl.up_down++;
		  else key_ctrl.up_down=0;
		  lcd_display.state=LCD_DISPLAY_SYSTEM_SET;
		}
	}

	hal_set_key_press(KEY_NULL);
}

static void key1_long(void)
{
	lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
	lcd_display.real_state=LCD_DISPLAY_MENU;
	key_ctrl.up_down=0;
	hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);

	hal_set_key_press(KEY_NULL);
}

static void key2_short(void)
{

}

static void key2_long(void)
{

}

static void key3_short(void)
{
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_MENU)
	{
		if(key_ctrl.up_down==0)
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
		  key_ctrl.up_down=0;
		  hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
		}
		else if(key_ctrl.up_down==5)
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_SYSTEM;
		  key_ctrl.up_down=0;
		  hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
	{
		if(key_ctrl.up_down==2)
		{
			lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_MENU;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
		}
		else
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_LASER_CTRL_SET;
		  lcd_display.laser_set=key_ctrl.up_down+1;
		}
		key_ctrl.up_down=0;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
	{
		if(lcd_display.laser_set==1 && key_ctrl.up_down!=(LASER_CTRL_MODE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
			hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			laser_ctrl.mode_value=key_ctrl.up_down;
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
		else if(lcd_display.laser_set==2 && key_ctrl.up_down!=(LASER_CTRL_STATE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
			hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			laser_ctrl.state_value=key_ctrl.up_down;
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
		if(key_ctrl.up_down==(LASER_CTRL_MODE_SET_NUM-1)||key_ctrl.up_down==(LASER_CTRL_STATE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
			hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
	{
		if(key_ctrl.up_down==0)
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM_SET;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_SYSTEM_SET;
		  lcd_display.system_set=key_ctrl.up_down+1;
		}
		else if(key_ctrl.up_down==1)
		{
			lcd_display.state=LCD_DISPLAY_INIT;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_INIT;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
		}
		else if(key_ctrl.up_down==2)
		{
			lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_MENU;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
		}
		else
		{
//			lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;//will turn to gif
//		  lcd_display.real_state=LCD_DISPLAY_LASER_CTRL_SET;
//		  lcd_display.laser_set=key_ctrl.up_down+1;
		}
		key_ctrl.up_down=0;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
	{
		if(lcd_display.system_set==1 && key_ctrl.up_down!=(LASER_CTRL_LANGUAGE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_SYSTEM;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
			lcd_display.language_value=key_ctrl.up_down;
			key_ctrl.up_down=0;
			lcd_display.system_set=0;
		}
		if(key_ctrl.up_down==(LASER_CTRL_LANGUAGE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_SYSTEM;
      hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
	}
	hal_set_key_press(KEY_NULL);
}

static void key3_long(void)
{

}

static void key_default(void)
{
	
}

