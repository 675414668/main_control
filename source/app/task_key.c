#include "task_key.h"
#include "task_lcd.h"
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

static uint8_t lcd_state = 0;
static uint8_t lcd_real_state = 0;

static void key_null(void);
static void key1_short(void);
static void key1_long(void);
static void key2_short(void);
static void key2_long(void);
static void key3_short(void);
static void key3_long(void);
static void key_default(void);

void task_key_init(void)
{
	hal_key_init();
	lcd_state = KEY_NULL;
	lcd_real_state = KEY_NULL;
}

void task_key_scan(void)
{
	lcd_state=lcd_get_display_state();
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

static void key_null(void)
{
	
}

static void key1_short(void)
{
	if(lcd_state==LCD_DISPLAY_ASTRONAUT)
	{
		if(lcd_real_state==LCD_DISPLAY_INIT)
		{
			lcd_set_display_state(LCD_DISPLAY_MENU);
			lcd_real_state=LCD_DISPLAY_MENU;
		}			
		else if(lcd_real_state==LCD_DISPLAY_MENU)
		{
			lcd_set_display_state(LCD_DISPLAY_INIT);
			lcd_real_state=LCD_DISPLAY_INIT;
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
