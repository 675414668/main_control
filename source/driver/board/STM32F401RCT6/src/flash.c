#include "flash.h"

void bsp_flash_ulock(void)
{
	 FLASH_Unlock();
}

void bsp_flash_erase_sector(uint32_t sector)
{
	FLASH_EraseSector(sector,VoltageRange_3);
}

void bsp_flash_write_word(uint32_t addr, uint32_t *data,uint32_t num)
{
	uint32_t i=0;
	for(i=0;i<num;i++)
	{
		FLASH_ProgramWord(addr,*(data+i));
	}
}

int32_t bsp_flash_read_word(uint32_t addr)
{
	return *(int32_t*)addr;
}

uint32_t bsp_flash_get_sector(uint32_t addr)
{
  uint32_t sector = 0;
  if(addr>=ADDR_SECTOR0 && addr<ADDR_SECTOR1)
	{
		sector=FLASH_Sector_0;
	}
	else if(addr>=ADDR_SECTOR1 && addr<ADDR_SECTOR2)
	{
		sector=FLASH_Sector_1;
	}
	else if(addr>=ADDR_SECTOR2 && addr<ADDR_SECTOR3)
	{
	  sector=FLASH_Sector_2;
	}
	else if(addr>=ADDR_SECTOR3 && addr<ADDR_SECTOR4)
	{
		sector=FLASH_Sector_3;
	}
		else if(addr>=ADDR_SECTOR4 && addr<ADDR_SECTOR5)
	{
		sector=FLASH_Sector_4;
	}
	else if(addr>=ADDR_SECTOR5)
	{
		sector=FLASH_Sector_5;
	}
  return sector;
}
