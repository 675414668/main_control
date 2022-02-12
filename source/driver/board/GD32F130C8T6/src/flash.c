#include "flash.h"


#define FMC_PAGE_SIZE           ((uint16_t)0x400)
#define GD_START_ADDR  ((uint32_t)0x08000000)

void bsp_flash_ulock(void)
{
	 fmc_unlock();
}

void bsp_flash_erase_sector(uint32_t sector)
{
	fmc_page_erase(GD_START_ADDR + (FMC_PAGE_SIZE * sector));
}

void bsp_flash_write_word(uint32_t addr, uint32_t *data,uint32_t num)
{
	uint32_t i=0;
	for(i=0;i<num;i++)
	{
		fmc_word_program(addr,*(data+i));
  
	}
}

int32_t bsp_flash_read_word(uint32_t addr)
{
	return *(int32_t*)addr;
}

uint32_t bsp_flash_get_sector(uint32_t addr)
{
	uint32_t sector=0;
  sector=(addr-GD_START_ADDR)/FMC_PAGE_SIZE;
  return sector;
}
