#include "hal_usart.h"

void hal_usart_init(uint32_t boadrate)
{
   bsp_usart_com_init(boadrate);
}
