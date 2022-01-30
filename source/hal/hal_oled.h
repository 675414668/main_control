#ifndef __HAL_OLED_H
#define __HAL_OLED_H

#include "oled.h"

void hal_oled_init(void);
void hal_oled_set_pos(unsigned char x, unsigned char y) ;//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
void hal_oled_display_on(void);// 开启OLED显示
void hal_oled_display_off(void);// 关闭OLED显示   
void hal_oled_clear(void);//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
void hal_oled_show_char(uint8_t x,uint8_t y,uint8_t chr);//在指定位置显示一个字符,包括部分字符x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
void hal_oled_show_char_adjust(uint8_t size,uint8_t x,uint8_t y,uint8_t chr);//在指定位置显示一个字符,可调节字符大小 x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
uint32_t hal_oled_pow(uint8_t m,uint8_t n);//m^n函数
void hal_oled_show_num(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);//显示2个数字
void hal_oled_show_string(uint8_t x,uint8_t y,char *chr);
void hal_oled_draw_bmp(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

#endif 


