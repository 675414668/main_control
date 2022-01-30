#include "hal_oled.h"

void hal_oled_init(void)
{
   bsp_oled_init();
}

void hal_oled_set_pos(unsigned char x, unsigned char y) 
{
	bsp_oled_set_pos(x,y);
}

void hal_oled_display_on(void)
{
	bsp_oled_display_on();
}

void hal_oled_display_off(void)
{
	bsp_oled_display_off();
}

void hal_oled_clear(void) 
{
	bsp_oled_clear();
}	

void hal_oled_show_char(uint8_t x,uint8_t y,uint8_t chr)
{
	bsp_oled_show_char(x,y,chr);
}

void hal_oled_show_char_adjust(uint8_t size,uint8_t x,uint8_t y,uint8_t chr)
{
	bsp_oled_show_char_adjust(size,x,y,chr);
}

uint32_t hal_oled_pow(uint8_t m,uint8_t n)
{
	return bsp_oled_pow(m,n);
}

void hal_oled_show_num(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{
	bsp_oled_show_num( x,y,num,len,size);
}

void hal_oled_show_string(uint8_t x,uint8_t y,char *chr)
{
	bsp_oled_show_string( x,y,chr);
}

void hal_oled_draw_bmp(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
	 unsigned int j=0;
   unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		bsp_oled_set_pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	bsp_oled_write_byte(BMP[j++],OLED_DATA);	    	
	    }
	}
}
