#include "task_adc.h"
#include "FreeRTOS.h"
#include "task.h"

float adc_voltage = 0;
uint32_t pwm_pulse = 0;
uint8_t task_adc_stack = 0;
static void task_adc_for_pwm(void *pvParameters);

void task_adc_init(void)
{
		hal_timer_init();
	  hal_adc_init();
	  hal_tim_pwm_enable();
	  osal_task_creats(task_adc_for_pwm,NULL,79,1);
}

static void task_adc_for_pwm(void *pvParameters)
{
   while(1)
	 {
		 	adc_voltage=hal_read_adc_data_voltage(ADC_FOR_PWM);                        
		  printf("ADC data:%f\r\n",adc_voltage);
	    //œﬂ–‘≤Â÷µ
	    pwm_pulse = 1000/3.3*adc_voltage;
	    hal_tim_pwm_pulse_adjust(pwm_pulse);
		  osal_msleep(100);
 		  task_adc_stack=uxTaskGetStackHighWaterMark(NULL);
	 }

}


