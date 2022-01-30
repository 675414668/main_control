#include "usart.h"

static uint8_t usart_rx_buff[USART_RX_SIZE]={0};
static uint8_t usart_rx_data_num=0;
static uint8_t usart_rx_begin_flag=0;
static uint8_t usart_rx_get_over_flag=0;

static void bsp_usart_gpio_init(void);
static void bsp_usart_driver_init(void);
static uint8_t bsp_usart_rx_begin_flag_get(void);
static uint8_t bsp_usart_rx_begin_flag_set(void);
static uint8_t bsp_usart_rx_begin_flag_clear(void);

void bsp_usart_com_init(void)
{
  bsp_usart_gpio_init();
	bsp_usart_driver_init();
}

static void bsp_usart_gpio_init(void)
{
  gpio_af_set(USART_COM_PORT, GPIO_AF_1, USART_COM_TX_PIN);
  gpio_af_set(USART_COM_PORT, GPIO_AF_1, USART_COM_RX_PIN);

  gpio_mode_set(USART_COM_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART_COM_TX_PIN);
  gpio_output_options_set(USART_COM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART_COM_TX_PIN);

  gpio_mode_set(USART_COM_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART_COM_RX_PIN);
  gpio_output_options_set(USART_COM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART_COM_RX_PIN);
}

static void bsp_usart_driver_init(void)
{
  usart_deinit(USART_COM);
  usart_word_length_set(USART_COM, USART_WL_8BIT);
  usart_stop_bit_set(USART_COM, USART_STB_1BIT);
  usart_parity_config(USART_COM, USART_PM_NONE);
  usart_baudrate_set(USART_COM, USART_COM_BAUDRATE);
  usart_receive_config(USART_COM, USART_RECEIVE_ENABLE);
  usart_transmit_config(USART_COM, USART_TRANSMIT_ENABLE);

  nvic_irq_enable(USART_COM_IRQn, 0);
  usart_interrupt_enable(USART_COM,USART_INT_RBNE);

  usart_enable(USART_COM);
}

void bsp_usart_com_enable(void)
{
  usart_enable(USART_COM);
}

void bsp_usart_com_disable(void)
{
  usart_disable(USART_COM);
}

void bsp_usart_com_send_data(uint32_t * input_data,uint32_t data_length)
{
  uint32_t i,data;
  for(i=0;i<data_length;i++)
  {
    data = input_data[i];
    usart_data_transmit(USART_COM,data);
  }
}

static uint8_t bsp_usart_rx_begin_flag_get(void)
{
  return usart_rx_begin_flag;
}

static uint8_t bsp_usart_rx_begin_flag_set(void)
{
  usart_rx_begin_flag = 1;
  return 0;
}

static uint8_t bsp_usart_rx_begin_flag_clear(void)
{
  usart_rx_begin_flag = 0;
  return 0;
}

uint8_t bsp_usart_rx_get_over_flag_get(void)
{
  return usart_rx_get_over_flag;
}

uint8_t bsp_usart_rx_get_over_flag_set(void)
{
  usart_rx_get_over_flag = 1;
  return 0;
}

uint8_t bsp_usart_rx_get_over_flag_clear(void)
{
  usart_rx_get_over_flag = 0;
  return 0;
}

void USART0_IRQHandler(void)
{
  uint8_t data;
    if(RESET != usart_interrupt_flag_get(USART_COM, USART_INT_FLAG_RBNE))
    {
      data = usart_data_receive(USART_COM);
      if(data==0x8a)
      {
         usart_rx_buff[usart_rx_data_num] = data;
         usart_rx_data_num++;
         if(usart_rx_data_num==2)
         {
           bsp_usart_rx_begin_flag_set();
         }
      }
      if(bsp_usart_rx_begin_flag_get()==1)
      {
        usart_rx_buff[usart_rx_data_num]=data;
        if(usart_rx_buff[usart_rx_data_num]==0x66 && usart_rx_buff[usart_rx_data_num-1]==0x66)
        {
          usart_rx_data_num = 0;
          bsp_usart_rx_begin_flag_clear();
          bsp_usart_rx_get_over_flag_set();
        }
      } 
    }
}

