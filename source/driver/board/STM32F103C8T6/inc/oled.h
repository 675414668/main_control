#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "string.h"
#include "osal.h"

#define OLED_MODE 				0//0:4线串行模式 1:并行8080模式
#define SIZE 					    16
#define XLevelL						0x00
#define XLevelH						0x10
#define Max_Column				128
#define Max_Row						64
#define	Brightness				0xFF 
#define X_WIDTH 					128
#define Y_WIDTH 					64	    

#define OLED_CMD  0				//写命令
#define OLED_DATA 1				//写数据

#define  OLED_GPIO_PORT   GPIOB		
#define  OLED_D0_PORT     GPIOB			
#define  OLED_D1_PORT     GPIOB							
#define  OLED_RES_PORT    GPIOB		
#define  OLED_DC_PORT     GPIOB				

#define  OLED_D0_Pin      GPIO_Pin_5				/* D0 */
#define  OLED_D1_Pin      GPIO_Pin_6				/* D1 */
#define  OLED_RES_Pin     GPIO_Pin_7				/* RES */
#define  OLED_DC_Pin     	GPIO_Pin_8				/* DC */

void bsp_oled_init(void);
void bsp_oled_write_byte(uint8_t dat,uint8_t cmd);
void bsp_oled_set_pos(unsigned char x, unsigned char y) ;//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
void bsp_oled_display_on(void);// 开启OLED显示
void bsp_oled_display_off(void);// 关闭OLED显示   
void bsp_oled_clear(void);//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
void bsp_oled_show_char(uint8_t x,uint8_t y,uint8_t chr);//在指定位置显示一个字符,包括部分字符x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
void bsp_oled_show_char_adjust(uint8_t size,uint8_t x,uint8_t y,uint8_t chr);//在指定位置显示一个字符,可调节字符大小 x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
uint32_t bsp_oled_pow(uint8_t m,uint8_t n);//m^n函数
void bsp_oled_show_num(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);//显示2个数字
void bsp_oled_show_string(uint8_t x,uint8_t y,char *chr);

#endif 
