#include "task_lcd.h"
#include "pic.h"
#define BACK_COLOR  0x0000


void task_lcd_init(void)
{
	bsp_lcd_init();//LCD≥ı ºªØ
	hal_lcd_draw_fill(BACK_COLOR);

}


void task_lcd_display(void)
{
	hal_lcd_show_picture(115,99,45,38,gImage_0);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_1);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_2);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_3);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_4);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_5);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_6);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_7);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_8);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_9);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_10);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_11);
	hal_delay_ms(20);
	hal_lcd_show_picture(115,99,45,38,gImage_12);
	hal_delay_ms(20);
  hal_lcd_show_picture(115,99,45,38,gImage_13);
	hal_delay_ms(20);
}

