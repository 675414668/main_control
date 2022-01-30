#include "adc.h"


static void bsp_adc_driver_init(void);

void bsp_adc_init(void)
{
  bsp_adc_driver_init();
}

static void bsp_adc_driver_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;                                                    
	GPIO_InitTypeDef GPIO_InitStructure;                                                          
	
	RCC_ADCCLKConfig(ADC_FOR_PWM_CLK_DIV) ;   //时钟分频72M/8=9M 最大时钟不超过14M

	
	GPIO_InitStructure.GPIO_Pin = ADC_FOR_PWM_GPIO_PIN;                                             
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                                         
	GPIO_Init(ADC_FOR_PWM_GPIO_PORT, &GPIO_InitStructure);                                                
	
  ADC_DeInit(ADC_FOR_PWM);                                                                        
  ADC_DMACmd(ADC_FOR_PWM, DISABLE);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;    	//ADC 独立工作模式                               
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  	        //是否扫描_单通道                                      
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;     //是否连续_单次                           
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;    //不用外部触发，软件触发转换 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   	             //数据右对齐                             
	ADC_InitStructure.ADC_NbrOfChannel = 1;                                //ADC-通道个数_单通道                                   
	ADC_Init(ADC_FOR_PWM, &ADC_InitStructure);                                                   
	
	ADC_RegularChannelConfig(ADC_FOR_PWM, ADC_FOR_PWM_CH, 1, ADC_FOR_PWM_SAMOLE_TIME);     //配置内容和ADC外设的具体对接函数   (ADC端口 ,ADC通道 ,转换序号-第几个转换 ,转换的周期)            
	
	ADC_Cmd(ADC_FOR_PWM,ENABLE); 
  ADC_ResetCalibration(ADC_FOR_PWM);   //ADC寄存器复位校准函数	
	while(ADC_GetResetCalibrationStatus(ADC_FOR_PWM)); //等待上一步完成
  ADC_StartCalibration(ADC_FOR_PWM);//开始指定ADC的校准状态
  while(ADC_GetCalibrationStatus(ADC_FOR_PWM)); //等待上一步完成               
}

uint32_t bsp_read_adc_data(ADC_TypeDef* ADCx)
{
	uint32_t data=0;                                                                                                                                                                                                                                                                                                                                                               
	
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);       //开关_ADC软件触发-开关    状态寄存器为0                                                                  
				
	while(!ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC));   //等待转换结束             寄存器置1                                                                            
			
	data=ADC_GetConversionValue(ADCx);                                                                                                              
	
	return data;                                                                            
	//返回电压值                                          
}

float bsp_read_adc_data_voltage(ADC_TypeDef* ADCx)
{
	float data=0;                                                                                                                                                                                                                                                                                                                                                               
	
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);       //开关_ADC软件触发-开关    状态寄存器为0                                                                  
				
	while(!ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC));   //等待转换结束             寄存器置1                                                                            
			
	data=(3.3*(((float)ADC_GetConversionValue(ADCx)/4096)));                                
	//百分比值转化成电压值，    因为读取了数据寄存器，状态寄存器自动清0                                                                                    
	
	return data;                                                                            
	//返回电压值                                          
}

