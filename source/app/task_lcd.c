#include "task_lcd.h"
#include "pic.h"

enum
{
	DISPLAY_INIT=0,
	DISPLAY_ASTRONAUT,
};

typedef struct 
{
	uint8_t state;
}lcd_display_t;
lcd_display_t lcd_display;

static void lcd_show_init(void);
static void lcd_show_astronaut(void);

void task_lcd_init(void)
{
	hal_lcd_init();
	hal_lcd_draw_fill(BLACK);
	lcd_display.state=DISPLAY_INIT;
}

static void lcd_show_init(void)
{
	hal_lcd_show_string(30,0,(uint8_t *)"system begin",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,16,(uint8_t *)"system clock set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,32,(uint8_t *)"cpu frequency:80M HZ",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,48,(uint8_t *)"usart set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,64,(uint8_t *)"usaer 1baudrate:115200",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,80,(uint8_t *)"led set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,96,(uint8_t *)"keyboard set over",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,112,(uint8_t *)"hardware version:V1.0.0",BRRED,BLACK,16,0);
	hal_lcd_show_string(30,128,(uint8_t *)"software version:V1.0.0",BRRED,BLACK,16,0);
	lcd_display.state=DISPLAY_ASTRONAUT;//Ìø×ªµ½Óîº½Ô±
}

static void lcd_show_astronaut(void)
{
	hal_lcd_show_picture(235,200,45,38,gImage_0);
	hal_lcd_show_picture(235,200,45,38,gImage_1);
	hal_lcd_show_picture(235,200,45,38,gImage_2);
	hal_lcd_show_picture(235,200,45,38,gImage_3);
	hal_lcd_show_picture(235,200,45,38,gImage_4);
	hal_lcd_show_picture(235,200,45,38,gImage_5);
	hal_lcd_show_picture(235,200,45,38,gImage_6);
	hal_lcd_show_picture(235,200,45,38,gImage_7);
	hal_lcd_show_picture(235,200,45,38,gImage_8);
	hal_lcd_show_picture(235,200,45,38,gImage_9);
	hal_lcd_show_picture(235,200,45,38,gImage_10);
	hal_lcd_show_picture(235,200,45,38,gImage_11);
	hal_lcd_show_picture(235,200,45,38,gImage_12);
  hal_lcd_show_picture(235,200,45,38,gImage_13);
}

void task_lcd_display(void)
{
	switch(lcd_display.state)
	{
		case DISPLAY_INIT:{ lcd_show_init();               break ;}
		case DISPLAY_ASTRONAUT:{ lcd_show_astronaut();     break ;}
		default: {break;}
			
	}
}

