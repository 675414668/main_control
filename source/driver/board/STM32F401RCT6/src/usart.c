#include "usart.h"

static void bsp_usart1_gpio_init(void);
static void bsp_usart1_driver_init(uint32_t boadrate);

void bsp_usart_com_init(uint32_t boadrate)
{
  bsp_usart1_gpio_init();
	bsp_usart1_driver_init(boadrate);
}

static void bsp_usart1_gpio_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(USART_COM_PORT,USART_COM_TX_SOURCE,GPIO_AF_USART1);
	GPIO_PinAFConfig(USART_COM_PORT,USART_COM_RX_SOURCE,GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = USART_COM_TX_PIN|USART_COM_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(USART_COM_PORT, &GPIO_InitStructure);
}

static void bsp_usart1_driver_init(uint32_t boadrate)
{
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	USART_InitStructure.USART_BaudRate = boadrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART_COM, &USART_InitStructure);
	
  USART_Cmd(USART_COM, ENABLE);
}

/*printf*/
int fputc(int ch, FILE *f)
{      
	USART_SendData(USART_COM, (uint8_t) ch);
	while(USART_GetFlagStatus(USART_COM, USART_FLAG_TC) == RESET);//循环发送,直到发送完毕       
	return ch;
}
