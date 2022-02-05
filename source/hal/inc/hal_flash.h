#ifndef __HAL_FLASH_H
#define __HAL_FLASH_H

#include "flash.h"

void hal_flash_user_data_init(void);
void hal_flash_ulock(void);
void hal_flash_erase_sector(uint32_t sector);
void hal_flash_write_word(uint32_t addr, uint32_t *data,uint32_t num);
int32_t hal_flash_read_word(uint32_t addr);
uint32_t hal_flash_get_sector(uint32_t addr);
void hal_set_user_data(uint8_t data_state,uint32_t data);
uint32_t hal_get_user_data(uint8_t data_state);
#endif 
