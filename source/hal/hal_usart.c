#include "hal_usart.h"

void hal_usart_init(void)
{
   bsp_usart_init();
}

void hal_uasrt_hex_display(uint8_t* lcd_data)
{
		uint8_t usart_rx_data[127];
		uint8_t i,count=0;
		if(bsp_get_usart_rx_over_flag()==1)
	{
		bsp_clear_usart_rx_over_flag();
		bsp_get_usart_rx_data(usart_rx_data);
		for(i=0;i<bsp_get_usart_rx_count();i++)
	{
    lcd_data[count*3]=usart_rx_data[i]>>4&0x0F;
		lcd_data[count*3+1]=usart_rx_data[i]&0x0F;
		lcd_data[count*3+2]=32;
		if(lcd_data[count*3]<10)
		{
			lcd_data[count*3]=lcd_data[count*3]+0x30;
		}
		else
		{
			lcd_data[count*3]=lcd_data[count*3]+0x37;
		}
		if(lcd_data[count*3+1]<10)
		{
			lcd_data[count*3+1]=lcd_data[count*3+1]+0x30;
		}
		else
		{
			lcd_data[count*3+1]=lcd_data[count*3+1]+0x37;
		}
		count++;
	}
	bsp_clear_usart_rx_count();
	bsp_clear_usart_rx_buff();
 }
}

void hal_uasrt_dec_display(uint8_t* lcd_data)
{
	bsp_get_usart_rx_data(lcd_data);
	bsp_clear_usart_rx_count();
	bsp_clear_usart_rx_buff();
}
