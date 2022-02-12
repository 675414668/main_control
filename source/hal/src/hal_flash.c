#include "hal_flash.h"

uint32_t user_data[USER_DATA_NUM]={0};

void hal_flash_user_data_init(void)
{
	uint8_t i=0;
	uint32_t sector=0;
	bsp_flash_ulock();
	user_data[0]=bsp_flash_read_word(USER_DATA_ADDR);
	if(user_data[0]==0xFFFFFFFF)//data init
	{
		user_data[CHAR_MCU_TYPE]=MCU_TYPE;
		user_data[CHAR_LANGUAGE_DATA]=1;//CHINESE
		
		sector=bsp_flash_get_sector(USER_DATA_ADDR);
		bsp_flash_erase_sector(sector);
		bsp_flash_write_word(USER_DATA_ADDR,user_data,USER_DATA_NUM);

	}
	else
	{
		for(i=0;i<USER_DATA_NUM;i++)
		{
			user_data[i]=bsp_flash_read_word(USER_DATA_ADDR+4*i);
		}
	}

}

void hal_flash_ulock(void)
{
	 bsp_flash_ulock();
}

void hal_flash_erase_sector(uint32_t sector)
{
	bsp_flash_erase_sector(sector);
}

void hal_flash_write_word(uint32_t addr, uint32_t *data,uint32_t num)
{
	bsp_flash_write_word(addr,data,num);
}

int32_t hal_flash_read_word(uint32_t addr)
{
	return bsp_flash_read_word(addr);
}

uint32_t hal_flash_get_sector(uint32_t addr)
{
	return bsp_flash_get_sector(addr);
}

void hal_set_user_data(uint8_t data_state,uint32_t data)
{
	uint32_t sector=0;
	if(data_state==CHAR_LANGUAGE_DATA)
	{
		user_data[CHAR_LANGUAGE_DATA]=data;
	}
	sector=bsp_flash_get_sector(USER_DATA_ADDR);
	bsp_flash_erase_sector(sector);
	bsp_flash_write_word(USER_DATA_ADDR,user_data,USER_DATA_NUM);
}

uint32_t hal_get_user_data(uint8_t data_state)
{
	return user_data[data_state];
}
