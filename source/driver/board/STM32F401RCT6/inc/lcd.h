#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx.h"
#include "string.h"
#include "osal.h"
#include "delay.h"

#define LCD_CONTROL_RCU  RCC_AHB1Periph_GPIOA
#define LCD_CONTROL_PORT GPIOA
#define LCD_CONTROL_RES  GPIO_Pin_8
#define LCD_CONTROL_DC   GPIO_Pin_2
#define LCD_CONTROL_BLK  GPIO_Pin_1
#define LCD_CONTROL_CS1  GPIO_Pin_3
#define LCD_CONTROL_CS2  GPIO_Pin_4

#define LCD_CONTROL_SCK       GPIO_Pin_5
#define LCD_CONTROL_MISO      GPIO_Pin_6
#define LCD_CONTROL_SDA       GPIO_Pin_7

#define LCD_SPI               SPI1
#define LCD_SPI_RCU           RCC_APB2Periph_SPI1


#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 280

#else
#define LCD_W 280
#define LCD_H 240
#endif



//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCK_RESET()   GPIO_ResetBits(LCD_CONTROL_PORT,LCD_CONTROL_SCK)//SCK
#define LCD_SCK_SET()     GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_SCK)

#define LCD_SDA_RESET()     GPIO_ResetBits(LCD_CONTROL_PORT,LCD_CONTROL_SDA)//SDA
#define LCD_SDA_SET()     GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_SDA)

#define LCD_RES_RESET()   GPIO_ResetBits(LCD_CONTROL_PORT,LCD_CONTROL_RES)//RES
#define LCD_RES_SET()     GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_RES)

#define LCD_DC_RESET()    GPIO_ResetBits(LCD_CONTROL_PORT,LCD_CONTROL_DC)//DC
#define LCD_DC_SET()      GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_DC)

#define LCD_BLK_RESET()   GPIO_ResetBits(LCD_CONTROL_PORT,LCD_CONTROL_BLK)//BLK
#define LCD_BLK_SET()     GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_BLK)

#define LCD_MISO_READ     GPIO_ReadInputDataBit(LCD_CONTROL_PORT,LCD_CONTROL_MISO)//MISO  ��ȡ�ֿ���������

#define LCD_CS1_RESET()   GPIO_ResetBits(LCD_CONTROL_PORT,LCD_CONTROL_CS1)//CS1
#define LCD_CS1_SET()     GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_CS1)

#define LCD_CS2_RESET()   GPIO_ResetBits(LCD_CONTROL_PORT,LCD_CONTROL_CS2)//CS2 �ֿ�Ƭѡ
#define LCD_CS2_SET()     GPIO_SetBits(LCD_CONTROL_PORT,LCD_CONTROL_CS2)	

void bsp_lcd_gpio_init(void);//��ʼ��GPIO
void bsp_lcd_write_bus(uint8_t dat);//ģ��SPIʱ��
void bsp_lcd_write_8bit(uint8_t dat);//д��һ���ֽ�
void bsp_lcd_write_16bit(uint16_t dat);//д�������ֽ�
void bsp_lcd_write_reg(uint8_t dat);//д��һ��ָ��
void bsp_lcd_set_addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void bsp_lcd_init(void);//LCD��ʼ��

#endif 


