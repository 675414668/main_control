#ifndef __LCD_H
#define __LCD_H

#include "gd32f1x0.h"
#include "string.h"
#include "osal.h"
#include "delay.h"

#define LCD_CONTROL_RCU  RCU_GPIOA
#define LCD_CONTROL_PORT GPIOA
#define LCD_CONTROL_RES  GPIO_PIN_0
#define LCD_CONTROL_DC   GPIO_PIN_1
#define LCD_CONTROL_BLK  GPIO_PIN_2
#define LCD_CONTROL_CS1  GPIO_PIN_3
#define LCD_CONTROL_CS2  GPIO_PIN_4





#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 280

#else
#define LCD_W 280
#define LCD_H 240
#endif



//-----------------LCD�˿ڶ���---------------- 

#define LCD_RES_Clr()  gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_RES)//RES
#define LCD_RES_Set()  gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_RES)

#define LCD_DC_Clr()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_DC)//DC
#define LCD_DC_Set()   gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_DC)

#define LCD_BLK_Clr()  gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_BLK)//BLK
#define LCD_BLK_Set()  gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_BLK)

#define LCD_CS_Clr()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_CS1)//CS1
#define LCD_CS_Set()   gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_CS1)

#define ZK_CS_Clr()    gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_CS2)//CS2
#define ZK_CS_Set()    gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_CS2)		


void bsp_lcd_gpio_init(void);//��ʼ��GPIO
void bsp_lcd_write_bus(uint8_t dat);//ģ��SPIʱ��
void bsp_lcd_write_8bit(uint8_t dat);//д��һ���ֽ�
void bsp_lcd_write_16bit(uint16_t dat);//д�������ֽ�
void bsp_lcd_write_reg(uint8_t dat);//д��һ��ָ��
void bsp_lcd_set_addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void bsp_lcd_init(void);//LCD��ʼ��

#endif 


