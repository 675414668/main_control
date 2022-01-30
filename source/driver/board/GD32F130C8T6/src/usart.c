#include "usart.h"

#define USART_RX_NUM 127

uint8_t usart_rx_buff[USART_RX_NUM];
uint16_t usart_rx_count = 0;
uint8_t usart_rx_flag = 0;//接收到数据标志位


void bsp_usart_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);//GPIOB时钟使能
    rcu_periph_clock_enable(RCU_USART0);//USART0时钟使能

    gpio_af_set(GPIOB, GPIO_AF_0, GPIO_PIN_6|GPIO_PIN_7);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_6);//PB6配置成多功能
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_6);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_7);//PB7配置成多功能
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_7);

    usart_deinit(USART0);
    usart_baudrate_set(USART0,115200);//波特率配置成9600
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);//发送使能
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);//接收使能
    usart_enable(USART0);//USART0使能
	
	  nvic_irq_enable(USART0_IRQn, 0, 0);
    usart_interrupt_enable(USART0, USART_INT_RBNE);//接收中断打开
}

int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}

uint8_t bsp_get_usart_rx_flag(void)
{
	return usart_rx_flag;
}

void bsp_clear_usart_rx_flag(void)
{
	usart_rx_flag=0;
}

void bsp_get_usart_rx_data(uint8_t *data)
{
	memcpy(data,usart_rx_buff,USART_RX_NUM);
}

uint8_t bsp_get_usart_rx_count (void)
{
	return usart_rx_count;
}
void bsp_clear_usart_rx_count (void)
{
	usart_rx_count=0;
}
void bsp_clear_usart_rx_buff (void)
{
	uint8_t *data = 0;
	memcpy(data,usart_rx_buff,USART_RX_NUM);
}
void USART0_IRQHandler(void)
{
	uint8_t rx_data=0;
  rx_data = usart_data_receive(USART0);
	usart_rx_buff[usart_rx_count]=rx_data;
	usart_rx_count++;
	usart_rx_flag = 1;
}

