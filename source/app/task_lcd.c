#include "task_lcd.h"

#define BACK_COLOR  0x0000


void task_lcd_display(void)
{
	uint8_t lcd_usart_string_data[127*3];
	uint8_t lcd_time_data[14];

	hal_timer_display(lcd_time_data);
	//bsp_get_stopwatch_time_buff(lcd_time_data);
  hal_uasrt_hex_display(lcd_usart_string_data);
	//hal_uasrt_dec_display(lcd_string_data);
	hal_lcd_show_string(30,0,lcd_time_data,BRRED,BACK_COLOR,12,0);
	//hal_lcd_show_string(30,0,lcd_usart_string_data,BRRED,BACK_COLOR,12,0);
}

void task_lcd_init(void)
{
	bsp_lcd_init();//LCD≥ı ºªØ
	hal_lcd_draw_fill(BACK_COLOR);

}
