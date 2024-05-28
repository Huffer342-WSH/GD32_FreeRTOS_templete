#ifndef _BSP_UART_H_
#define _BSP_UART_H_
#include "gd32f3x0.h"

#ifdef __cplusplus
extern "C" {
#endif

#define USART1_DMA_TX_CHx DMA_CH3
#define USART1_DMA_RX_CHx DMA_CH4

void BSP_Uart_Init();
void UART_Transmit_DMA(void *pData, uint32_t size);
void UART_Receive_DMA(void *buf, uint32_t size);
uint8_t USART1_Get_Rx(uint32_t *addr, uint32_t *size);

#ifdef __cplusplus
}
#endif
#endif /* _BSP_UART_H_ */
