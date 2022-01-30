#include "key.h"

enum KEY_PRESS Key_press = KEY_IDLE;

void bsp_key_init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);//GPIOAʱ�Ӵ�
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12);//PA1���ó�����
	nvic_irq_enable(EXTI4_15_IRQn, 2U, 0U);//ʹ���ⲿ�ж�
	syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN10|EXTI_SOURCE_PIN11|EXTI_SOURCE_PIN12);//PA1���ӵ��ⲿ�ж�

	/* configure key EXTI line */
	exti_init(EXTI_10, EXTI_INTERRUPT, EXTI_TRIG_FALLING);//�½���
	exti_init(EXTI_11, EXTI_INTERRUPT, EXTI_TRIG_FALLING);//�½���
	exti_init(EXTI_12, EXTI_INTERRUPT, EXTI_TRIG_FALLING);//�½���
//	exti_interrupt_enable(EXTI_10);
//	exti_interrupt_enable(EXTI_11);
//	exti_interrupt_enable(EXTI_12);
	exti_interrupt_flag_clear(EXTI_10);//���־
	exti_interrupt_flag_clear(EXTI_11);//���־
	exti_interrupt_flag_clear(EXTI_12);//���־
}

/**************************************************************
 ** ������ :Key_NVIC_Configuration
 ** ����   :�����ж�����
 ** ����   :��
 ** ���   :��
 ** ����   :��
 ** ע��   :��
***************************************************************/
void EXTI4_15_IRQHandler(void)
{
    u32 count=0;
    if(exti_interrupt_flag_get(EXTI_10)!=RESET)
    {
        while(gpio_input_bit_get(GPIOA,GPIO_PIN_10) && count++<10000000);
        if(count>0x50)  Key_press = KEY1_S;
        if(count>5000000) Key_press = KEY1_L;
        exti_interrupt_flag_clear(EXTI_10);
    }
    if(exti_interrupt_flag_get(EXTI_12)!=RESET)
    {
        while(gpio_input_bit_get(GPIOA,GPIO_PIN_11)==0 && count++<10000000);
        if(count>0x50)  Key_press = KEY2_S;
        if(count>5000000) Key_press = KEY2_L;
        exti_interrupt_flag_clear(EXTI_12);
    }
    if(exti_interrupt_flag_get(EXTI_11)!=RESET)
    {
        while(gpio_input_bit_get(GPIOA,GPIO_PIN_12)==0 && count++<10000000);
        if(count>0x50)  Key_press = KEY3_S;
        if(count>5000000) Key_press = KEY3_L;
        exti_interrupt_flag_clear(EXTI_11);
    }   
}


