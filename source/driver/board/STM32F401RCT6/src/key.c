#include "key.h"
#include "led.h"

typedef  struct 
{
	uint8_t key1;
	uint8_t key2;
	uint8_t key3;
}key_count_t;
key_count_t key_count;

enum 
{
	KEY1_S=0,
	KEY1_L,
	KEY2_S,
	KEY2_L,
	KEY3_S,
	KEY3_L,
};

uint8_t key_press = 0;

static void bsp_key_gpio_init(void);
static void bsp_key_tim_init(void);
static void bsp_key_scan(void);

void bsp_key_init(void)
{
	bsp_key_gpio_init();
	bsp_key_tim_init();
}

static void bsp_key_gpio_init(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(KEY_RCC, ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = KEY1_PIN|KEY2_PIN|KEY3_PIN;
  GPIO_Init(KEY_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(KEY_PORT,KEY1_PIN|KEY2_PIN|KEY3_PIN);
}

static void bsp_key_tim_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	
	RCC_APB1PeriphClockCmd(KEY_TIM_RCC,ENABLE);
	
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period = KEY_TIM_PERIOD;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = KEY_TIM_PRESCALER;
	TIM_TimeBaseInit(KEY_TIM,&TIM_TimeBaseInitTypeStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_InitTypeStruct.NVIC_IRQChannel = KEY_TIM_IRQN;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	TIM_Cmd(KEY_TIM,ENABLE);
}	

static void bsp_key_scan(void)
{
	if(GPIO_ReadInputDataBit(KEY_PORT,KEY1_PIN)==0)
	{
		key_count.key1++;
		if(key_count.key1==50)       key_press = KEY1_S;
		else if(key_count.key1==200) key_press = KEY1_L;
	}
	else
	{
		key_count.key1=0;
	}
	if(GPIO_ReadInputDataBit(KEY_PORT,KEY2_PIN)==0)
	{
		key_count.key2++;
		if(key_count.key2==50)       key_press = KEY2_S;
		else if(key_count.key2==200) key_press = KEY2_L;
	}
	else
	{
		key_count.key2=0;
	}
	if(GPIO_ReadInputDataBit(KEY_PORT,KEY3_PIN)==0)
	{
		key_count.key3++;
	  if(key_count.key3==50)       key_press = KEY3_S;
		else if(key_count.key3==200) key_press = KEY3_L;
	}
	else
	{
		key_count.key3=0;
	}
}

uint8_t bsp_get_key_press(void)
{
	return key_press;
}
void KEY_TIM_IRQHANDLER(void)
{
	if(TIM_GetITStatus(KEY_TIM,TIM_IT_Update)==SET)
	{
		bsp_key_scan();
		TIM_ClearITPendingBit(KEY_TIM,TIM_IT_Update);
	}
	
	
}