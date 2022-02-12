#ifndef __FLASH_H
#define __FLASH_H

#include "gd32f1x0.h"
#include "string.h"


#define USER_DATA_ADDR (0x0800F800)
#define USER_DATA_NUM  (2)
#define MCU_TYPE       (2)  //写入1为stm32，写入2为gd32f130c8t6
#define CHAR_MCU_TYPE  (0)  //数组地址0，
#define CHAR_LANGUAGE_DATA  (1)

void bsp_flash_ulock(void);
void bsp_flash_erase_sector(uint32_t sector);
void bsp_flash_write_word(uint32_t addr, uint32_t *data,uint32_t num);
int32_t bsp_flash_read_word(uint32_t addr);
uint32_t bsp_flash_get_sector(uint32_t addr);
#endif 
