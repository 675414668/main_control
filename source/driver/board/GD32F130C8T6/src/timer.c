#include "timer.h"

uint16_t tim_irq_count = 0;
uint8_t usart_state = 0;
uint8_t last_usart_state = 0;
uint8_t usart_rx_over_flag = 0;//接收完成标志位

uint8_t sys_time_buff[14];
uint16_t ms=0;
uint8_t hour=0,min=0,sec=0;

uint8_t stopwatch_time_buff[14];
uint16_t stopwatch_ms=0;
uint8_t stopwatch_hour=0,stopwatch_min=0,stopwatch_sec=0;

static void bsp_tim_sys_init(void);
static void bsp_tim_stopwatch_init(void);
static void bsp_tim_usart_init(void);
static void bsp_set_timer_sys(void);
static void bsp_timer_stopwatch(void);

void bsp_timer_init(void)
{
	bsp_tim_sys_init();
	//bsp_tim_stopwatch_init();
	bsp_tim_usart_init();
}

static void bsp_tim_sys_init(void)
{
	  timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER2);

    timer_deinit(TIMER2);

    timer_initpara.prescaler         = TIM_SYS_PRESCALER;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = TIM_SYS_PERIOD;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);

		nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);//1 bit抢占优先级,3 bit子优先级，数值越小，优先级越高
		nvic_irq_enable(TIMER2_IRQn, 0, 1);//中断优先级使能
		timer_interrupt_enable(TIMER2, TIMER_INT_UP);
	
    timer_auto_reload_shadow_enable(TIMER2);//自动重装载影子比较器使能
    timer_enable(TIMER2);//使能定时器
}

static void bsp_tim_stopwatch_init(void)
{
	  timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER13);

    timer_deinit(RCU_TIMER13);

    timer_initpara.prescaler         = TIM_STOPWATCH_PRESCALER;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = TIM_STOPWATCH_PERIOD;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER13,&timer_initpara);

		nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);//1 bit抢占优先级,3 bit子优先级，数值越小，优先级越高
		nvic_irq_enable(TIMER13_IRQn, 0, 1);//中断优先级使能
		timer_interrupt_enable(TIMER13, TIMER_INT_UP);
	
    timer_auto_reload_shadow_enable(TIMER13);//自动重装载影子比较器使能
    timer_enable(TIMER13);//使能定时器
}

static void bsp_tim_usart_init(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);

    timer_deinit(TIMER1);

    timer_initpara.prescaler         = TIM_USART_PRESCALER;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = TIM_USART_PERIOD;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1,&timer_initpara);

		nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);//1 bit抢占优先级,3 bit子优先级，数值越小，优先级越高
		nvic_irq_enable(TIMER1_IRQn, 0, 1);//中断优先级使能
		timer_interrupt_enable(TIMER1, TIMER_INT_UP);
	
    timer_auto_reload_shadow_enable(TIMER1);//自动重装载影子比较器使能
    timer_enable(TIMER1);//使能定时器
}

uint8_t bsp_get_usart_rx_over_flag(void)
{
	return usart_rx_over_flag;
}

void bsp_clear_usart_rx_over_flag(void)
{
	usart_rx_over_flag=0;
}

void bsp_get_sys_time_buff(uint8_t *data)
{
	memcpy(data,sys_time_buff,14);
}

static void bsp_set_timer_sys(void)
{
	ms++;
	if(ms==1000)
	{
		ms=0;
		sec++;
	}
	if(sec==60)
	{
		sec=0;
		min++;
	}
	if(min==60)
	{
		min=0;
		hour++;
	}
	if(hour==24)
	{
		hour=0;
	}
	sys_time_buff[0]=91;
	sys_time_buff[1]=hour/10+0x30;
	sys_time_buff[2]=hour%10+0x30;
	sys_time_buff[3]=58;
	sys_time_buff[4]=min/10+0x30;
	sys_time_buff[5]=min%10+0x30;
	sys_time_buff[6]=58;
	sys_time_buff[7]=sec/10+0x30;
	sys_time_buff[8]=sec%10+0x30;
	sys_time_buff[9]=58;
	sys_time_buff[10]=ms/100+0x30;
	sys_time_buff[11]=(ms/10)%10+0x30;
	sys_time_buff[12]=ms%10+0x30;
	sys_time_buff[13]=93;
}

void bsp_get_stopwatch_time_buff(uint8_t *data)
{
	memcpy(data,stopwatch_time_buff,14);
}

static void bsp_timer_stopwatch(void)
{
	ms++;
	if(ms==1000)
	{
		ms=0;
		sec++;
	}
	if(sec==60)
	{
		sec=0;
		min++;
	}
	if(min==60)
	{
		min=0;
		hour++;
	}
	if(hour==24)
	{
		hour=0;
	}
	stopwatch_time_buff[0]=91;
	stopwatch_time_buff[1]=stopwatch_hour/10+0x30;
	stopwatch_time_buff[2]=stopwatch_hour%10+0x30;
	stopwatch_time_buff[3]=58;
	stopwatch_time_buff[4]=stopwatch_min/10+0x30;
	stopwatch_time_buff[5]=stopwatch_min%10+0x30;
	stopwatch_time_buff[6]=58;
	stopwatch_time_buff[7]=stopwatch_sec/10+0x30;
	stopwatch_time_buff[8]=stopwatch_sec%10+0x30;
	stopwatch_time_buff[9]=58;
	stopwatch_time_buff[10]=stopwatch_ms/100+0x30;
	stopwatch_time_buff[11]=(stopwatch_ms/10)%10+0x30;
	stopwatch_time_buff[12]=stopwatch_ms%10+0x30;
	stopwatch_time_buff[13]=93;
}

void TIMER1_IRQHandler(void)
{
	timer_flag_clear(TIMER1,TIMER_FLAG_UP);//清溢出中断
	tim_irq_count++;

	if(tim_irq_count==TIM_WAIT)
	{
		tim_irq_count=0;
	  last_usart_state = usart_state;
	  usart_state=bsp_get_usart_rx_flag();
	  bsp_clear_usart_rx_flag();
		if(usart_state!=last_usart_state)
		{
			usart_rx_over_flag = 1;
		}
	}
}

void TIMER2_IRQHandler(void)
{
	timer_flag_clear(TIMER2,TIMER_FLAG_UP);//清溢出中断
  bsp_set_timer_sys();
}

void TIMER0_IRQHandler(void)
{
	timer_flag_clear(TIMER0,TIMER_FLAG_UP);//清溢出中断
  bsp_timer_stopwatch();
}
