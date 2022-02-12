#include "usart.h"

static void bsp_usart_gpio_init(void);
static void bsp_usart_driver_init(uint32_t boadrate);

void bsp_usart_com_init(uint32_t boadrate)
{
  bsp_usart_gpio_init();
	bsp_usart_driver_init(boadrate);
}
static void bsp_usart_gpio_init(void)
{
	rcu_periph_clock_enable(RCU_USART_COM_PORT);//USART_COM_PORT时钟使能
	gpio_af_set(USART_COM_PORT, GPIO_AF_0, GPIO_PIN_6|GPIO_PIN_7);

	gpio_mode_set(USART_COM_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART_COM_TX_PIN);//PB6配置成多功能
	gpio_output_options_set(USART_COM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_6);

	gpio_mode_set(USART_COM_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART_COM_RX_PIN);//PB7配置成多功能
	gpio_output_options_set(USART_COM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_7);
}
static void bsp_usart_driver_init(uint32_t boadrate)
{
    rcu_periph_clock_enable(USART_COM_RCU);

    usart_deinit(USART_COM);
    usart_baudrate_set(USART_COM,boadrate);
    usart_transmit_config(USART_COM, USART_TRANSMIT_ENABLE);//发送使能
    usart_receive_config(USART_COM, USART_RECEIVE_ENABLE);//接收使能
    usart_enable(USART_COM);//USART_COM使能
	
	  nvic_irq_enable(USART_COM_IRQn, 0, 0);
    usart_interrupt_enable(USART_COM, USART_INT_RBNE);//接收中断打开
}

int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART_COM, (uint8_t)ch);
    while(RESET == usart_flag_get(USART_COM, USART_FLAG_TBE));
    return ch;
}

