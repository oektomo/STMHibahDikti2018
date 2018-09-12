/*
 * platform_config.h
 *
 *  Created on: Oct 19, 2017
 *      Author: otm
 */

#ifndef PLATFORM_CONFIG_H_
#define PLATFORM_CONFIG_H_

#include "stm32f10x.h"

#define S1RECORD 1
#define S1DATA 2
#define TIMER_SYSTICK 4
#define READ_PHERIPHERAL 8

#define INLINE_CODE
//#define USE_TRACE

  #define USARTrPi                   USART1
  #define USARTrPi_GPIO              GPIOA
  #define USARTrPi_CLK_APB2          RCC_APB2Periph_USART1
  #define USARTrPi_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTrPi_RxPin             GPIO_Pin_10
  #define USARTrPi_TxPin             GPIO_Pin_9
  #define USARTrPi_IRQn              USART1_IRQn
  #define USARTrPi_IRQHandler        USART1_IRQHandler

  #define USARTm8                   USART3
  #define USARTm8_GPIO              GPIOB
  #define USARTm8_CLK_APB1          RCC_APB1Periph_USART3
  #define USARTm8_GPIO_CLK          RCC_APB2Periph_GPIOB
  #define USARTm8_RxPin             GPIO_Pin_11
  #define USARTm8_TxPin             GPIO_Pin_10
  #define USARTm8_IRQn              USART3_IRQn
  #define USARTm8_IRQHandler        USART3_IRQHandler

  #define USARTdbg                   USART2
  #define USARTdbg_GPIO              GPIOA
  #define USARTdbg_CLK               RCC_APB1Periph_USART2
  #define USARTdbg_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTdbg_RxPin             GPIO_Pin_3
  #define USARTdbg_TxPin             GPIO_Pin_2
  #define USARTdbg_IRQn              USART2_IRQn
  #define USARTdbg_IRQHandler        USART2_IRQHandler

#define INPUT_PB_CLK_APB2	RCC_APB2Periph_GPIOB
#define INPUT_PA_CLK_APB2	RCC_APB2Periph_GPIOA
#define INPUT_PC_CLK_APB2	RCC_APB2Periph_GPIOC

#define INPUT_PH1_PIN	1
#define INPUT_PH1_PORT	GPIOB
#define INPUT_PH2_PIN	0
#define INPUT_PH2_PORT	GPIOB
#define INPUT_PH3_PIN	7
#define INPUT_PH3_PORT	GPIOA
#define INPUT_PH4_PIN	6
#define INPUT_PH4_PORT	GPIOA
#define INPUT_PH5_PIN	5
#define INPUT_PH5_PORT	GPIOA
#define INPUT_PH6_PIN	4
#define INPUT_PH6_PORT	GPIOA
#define INPUT_PH7_PIN	3
#define INPUT_PH7_PORT	GPIOA
#define INPUT_PH8_PIN	1
#define INPUT_PH8_PORT	GPIOA
#define INPUT_PH9_PIN	0
#define INPUT_PH9_PORT	GPIOA
#define INPUT_PH10_PIN	15
#define INPUT_PH10_PORT	GPIOC
#define INPUT_PH11_PIN	14
#define INPUT_PH11_PORT	GPIOC
#define INPUT_PH12_PIN	13
#define INPUT_PH12_PORT	GPIOC

#define OUTPUT_PORT1_3 GPIOB
#define OUTPUT_PIN1 12
#define OUTPUT_PIN2 13
#define OUTPUT_PIN3 14

#define OUTPUT_PORT4_6 GPIOA
#define OUTPUT_PIN4 11
#define OUTPUT_PIN5 12
#define OUTPUT_PIN6 15

#define OUTPUT_PORT7_9 GPIOB
#define OUTPUT_PIN7 3
#define OUTPUT_PIN8 4
#define OUTPUT_PIN9 5

#define PHERIPHERAL_AMOUNT 21

typedef struct {
	int id;
	uint8_t state;
} pheripheral_typedef;

#endif /* PLATFORM_CONFIG_H_ */
