/*
 * uart.h
 *
 *  Created on: Oct 19, 2017
 *      Author: otm
 */

#ifndef UART_H_
#define UART_H_

#define OS_INTEGER_UART_PRINTF_TMP_ARRAY_SIZE 100

#include "stm32f10x_usart.h"
#include "platform_config.h"

void initUART(USART_InitTypeDef* USART_InitStructure);
void initUART_GPIO();
void USART_Tx(USART_TypeDef* USARTx, uint8_t Data);
uint8_t USART_SendString(USART_TypeDef* USARTx, const char* AoChar);
int uart_printf(const char* format, ...);
void USARTRpiNVIC_Configuration(void);
void sendDataInt(int n);
void sendDataRx();
void printPheripheral(pheripheral_typedef* Pheripheral);
void testData();


#endif /* UART_H_ */
