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
	GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = USART_COM_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USART_COM_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = USART_COM_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USART_COM_PORT, &GPIO_InitStructure);
}

static void bsp_usart_driver_init(void)
{
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	NVIC_InitStructure.NVIC_IRQChannel = USART_COM_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = USART_COM_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART_COM, &USART_InitStructure);

  //USART_ITConfig(USART_COM, USART_IT_RXNE, ENABLE);

  USART_Cmd(USART_COM, ENABLE);
}

void bsp_usart_com_enable(void)
{
  USART_Cmd(USART_COM,ENABLE);
}

void bsp_usart_com_disable(void)
{
  USART_Cmd(USART_COM,DISABLE);
}

void bsp_usart_com_send_data(uint32_t * input_data,uint32_t data_length)
{
  uint32_t i,data;
  for(i=0;i<data_length;i++)
  {
    data = input_data[i];
    USART_SendData(USART_COM,data);
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

void USART1_IRQHandler(void)
{
  uint8_t data;
    if(RESET != USART_GetITStatus(USART_COM, USART_FLAG_RXNE))
    {
      data = USART_ReceiveData(USART_COM);
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
/*printf*/
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
