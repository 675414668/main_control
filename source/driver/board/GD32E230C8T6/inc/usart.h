#ifndef __USART_H
#define __USART_H

#include "gd32e23x.h"

#define USART_COM           USART0
#define USART_COM_IRQn      USART0_IRQn
#define USART_COM_PORT      GPIOA
#define USART_COM_TX_PIN    GPIO_PIN_9
#define USART_COM_RX_PIN    GPIO_PIN_10
#define USART_COM_BAUDRATE  (115200U)

#define USART_RX_SIZE       (1024/32)

void bsp_usart_com_init(void);
void bsp_usart_com_enable(void);
void bsp_usart_com_disable(void);
void bsp_usart_com_send_data(uint32_t * input_data,uint32_t data_length);
uint8_t bsp_usart_rx_get_over_flag_get(void);
uint8_t bsp_usart_rx_get_over_flag_set(void);
uint8_t bsp_usart_rx_get_over_flag_clear(void);
#endif 