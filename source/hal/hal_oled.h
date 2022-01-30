#ifndef __HAL_OLED_H
#define __HAL_OLED_H

#include "oled.h"

void hal_oled_init(void);
void hal_oled_set_pos(unsigned char x, unsigned char y) ;//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��
void hal_oled_display_on(void);// ����OLED��ʾ
void hal_oled_display_off(void);// �ر�OLED��ʾ   
void hal_oled_clear(void);//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��
void hal_oled_show_char(uint8_t x,uint8_t y,uint8_t chr);//��ָ��λ����ʾһ���ַ�,���������ַ�x:0~127   y:0~63   mode:0,������ʾ  1,������ʾ	 size:ѡ������ 16/12 
void hal_oled_show_char_adjust(uint8_t size,uint8_t x,uint8_t y,uint8_t chr);//��ָ��λ����ʾһ���ַ�,�ɵ����ַ���С x:0~127   y:0~63   mode:0,������ʾ  1,������ʾ	 size:ѡ������ 16/12 
uint32_t hal_oled_pow(uint8_t m,uint8_t n);//m^n����
void hal_oled_show_num(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);//��ʾ2������
void hal_oled_show_string(uint8_t x,uint8_t y,char *chr);
void hal_oled_draw_bmp(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

#endif 


