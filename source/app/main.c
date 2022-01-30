#include "stm32f4xx.h"

#define LED1_PIN GPIO_Pin_4
#define LED2_PIN GPIO_Pin_5

GPIO_InitTypeDef  GPIO_InitStructure;

int count=0;
int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  /* Configure PG6 and PG8 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,LED1_PIN);
	GPIO_SetBits(GPIOC,LED2_PIN);
    while(1)
		{


    }
}


