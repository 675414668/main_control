#include "task_lcd.h"
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
};

typedef struct 
{
	uint8_t state;
	uint8_t real_state;
	uint8_t astronaut_num;
}lcd_display_t;
lcd_display_t lcd_display;

static void lcd_data_init(void);
static void lcd_show_init(void);
static void lcd_show_astronaut(void);
static void lcd_show_menu(void);

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
		case LCD_DISPLAY_INIT:     { lcd_show_init();          break ;}
		case LCD_DISPLAY_ASTRONAUT:{ lcd_show_astronaut();     break ;}
		case LCD_DISPLAY_MENU:     { lcd_show_menu();          break ;}
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
	lcd_display.astronaut_num=0;
}

static void lcd_show_menu(void)
{
	hal_lcd_fill(0,0,280,145,BLACK);
	hal_lcd_fill(0,180,230,240,BLACK);
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
		}			
		else if(lcd_display.real_state==LCD_DISPLAY_MENU)
		{
			lcd_display.state=LCD_DISPLAY_INIT;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_INIT;
		}
	}
	
	hal_set_key_press(KEY_NULL);
	
}

static void key1_long(void)
{
	
}

static void key2_short(void)
{
	
}

static void key2_long(void)
{
	
}

static void key3_short(void)
{
	
}

static void key3_long(void)
{
	
}

static void key_default(void)
{
	
}

