/*
 * uart.c
 *
 *  Created on: Oct 19, 2017
 *      Author: otm
 */

#include "platform_config.h"
#include "uart.h"
#include "codec2_fifo.h"
#include <stdarg.h>
#include <stdio.h>

/*
 * to initialize our UART we need 3 things
 * RCC UART
 * UART configuration
 * UART ENABLE
 *
 * RCC GPIO
 * GPIO AF configuration
 */
void initUART(USART_InitTypeDef* USART_InitStructure)
{
	/* Configure GPIO for USART	 */
	initUART_GPIO();

	  /* Enable USARTrPi Clock */
	  RCC_APB2PeriphClockCmd(USARTrPi_CLK_APB2, ENABLE);

	  USART_InitStructure->USART_BaudRate = 115200;
	  USART_InitStructure->USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure->USART_StopBits = USART_StopBits_1;
	  USART_InitStructure->USART_Parity = USART_Parity_No;
	  USART_InitStructure->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  USART_Init(USARTrPi, USART_InitStructure);

	  /* Enable USARTm8 Clock */
	  RCC_APB1PeriphClockCmd(USARTm8_CLK_APB1, ENABLE);

	  USART_InitStructure->USART_BaudRate = 115200;
	  USART_InitStructure->USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure->USART_StopBits = USART_StopBits_1;
	  USART_InitStructure->USART_Parity = USART_Parity_No;
	  USART_InitStructure->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  USART_Init(USARTm8, USART_InitStructure);

	  // Enable interrupt
	  USART_ITConfig(USARTrPi, USART_IT_RXNE, ENABLE);
	  USART_ITConfig(USARTm8, USART_IT_RXNE, ENABLE);

	  USARTRpiNVIC_Configuration();

	  USART_Cmd(USARTrPi, ENABLE);
	  USART_Cmd(USARTm8, ENABLE);
}

/*
 * Enable RCC GPIO
 * initialize GPIO to AF
 */
void initUART_GPIO()
{
	  /* Enable GPIO UART clock */
	  RCC_APB2PeriphClockCmd(USARTm8_GPIO_CLK , ENABLE);

	  /* Enable GPIO UART clock */
	  RCC_APB2PeriphClockCmd(USARTrPi_GPIO_CLK , ENABLE);

	  GPIO_InitTypeDef GPIO_InitStructure;

	  /* Configure USARTrPi_RxPin Rx as input floating */
	  GPIO_InitStructure.GPIO_Pin = USARTrPi_RxPin;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(USARTrPi_GPIO, &GPIO_InitStructure);

	  /* Configure USARTm8_RxPin Rx as input floating */
	  GPIO_InitStructure.GPIO_Pin = USARTm8_RxPin;
	  GPIO_Init(USARTm8_GPIO, &GPIO_InitStructure);

	  /* Configure USARTrPi_TxPin Tx as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = USARTrPi_TxPin;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(USARTrPi_GPIO, &GPIO_InitStructure);

	  /* Configure USARTm8 Tx as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = USARTm8_TxPin;
	  GPIO_Init(USARTm8_GPIO, &GPIO_InitStructure);
}

#ifdef INLINE_CODE
inline void
__attribute__((always_inline))
#else
void
#endif
USART_Tx(USART_TypeDef* USARTx, uint8_t Data)
{

	while( !USART_GetFlagStatus(USARTx, USART_FLAG_TXE) );
	USART_SendData(USARTx, Data);
}

uint8_t USART_SendString(USART_TypeDef* USARTx, const char* AoChar)
{
	uint8_t i = 0;
	while(AoChar[i] != '\0')
	{
		USART_Tx(USARTx, AoChar[i]);
		i++;
	}
	return i;
}

int
uart_printf(const char* format, ...)
{
  int ret;
  va_list ap;

  va_start (ap, format);

  // TODO: rewrite it to no longer use newlib, it is way too heavy

  static char buf[OS_INTEGER_UART_PRINTF_TMP_ARRAY_SIZE];

  // Print to the local buffer
  ret = vsnprintf (buf, sizeof(buf), format, ap);
  if (ret > 0)
    {
      // Transfer the buffer to the device
      //ret = trace_write (buf, (size_t)ret);
	  ret = (int)USART_SendString(USARTrPi, buf);
    }

  va_end (ap);
  return ret;
}

extern uint8_t status1;
struct FIFO *rxDatarPi;
/*
 * USART1_IRQ HANDLER
 */
void USART1_IRQHandler(void)
{
	char Data;
	//Data = USART_ReceiveData(USARTrPi);
	//USART_SendData(USARTrPi, Data);

	  if(USART_GetITStatus(USARTrPi, USART_IT_RXNE) != RESET)
	  {
	    /* Read one byte from the receive data register */
	    Data = USART_ReceiveData(USARTrPi);

	    // check status to RECORD or to tell if the status ready.
	    if (Data == 'S') {
	    	status1 |= S1RECORD;
	    } else if ( (Data == 'E') && ((status1 & S1RECORD) == S1RECORD) ) {

	    	// check if the data is 9 if not, delete it.
	    	if(fifo_used(rxDatarPi) == 8) {
	    		status1 |= S1DATA;
		    	fifo_write(rxDatarPi, &Data, 1);
	    	} else {
	    		while (fifo_used(rxDatarPi)) {
	    			char temp;
	    			fifo_read(rxDatarPi, &temp, 1);
	    		}
	    	}

	    	status1 &= ~S1RECORD;
	    }

	    if ((status1 & S1RECORD) == S1RECORD)
	    	fifo_write(rxDatarPi, &Data, 1);

	    //USART_SendData(USARTrPi, fifo_used(rxDatarPi));
	    sendDataInt(fifo_used(rxDatarPi));

	  }

}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void USARTRpiNVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void sendDataInt(int n)
{
	char buffer[10];
	itoa(n, buffer, 10);
	uint8_t i = 0;
	while(buffer[i]!='\0') {
		USART_Tx(USARTrPi, buffer[i]);
		i++;
	}
}

void sendDataRx()
{
	short Data;
	while( Data != 'E') {
		fifo_read(rxDatarPi, &Data, 1);
		USART_Tx(USARTrPi, Data);
	}
}

void printPheripheral(pheripheral_typedef* Pheripheral)
{
	for (int i = 1; i <= PHERIPHERAL_AMOUNT; i++){
		USART_Tx(USARTrPi, 'S');
		sendDataInt(Pheripheral[i].id);
		USART_Tx(USARTrPi, '&');
		sendDataInt(Pheripheral[i].state);
		USART_Tx(USARTrPi, 'E');
		USART_Tx(USARTrPi, '\n');
		USART_Tx(USARTrPi, '\r');
	}
}

void testData()
{
	USART_Tx(USARTrPi, 'A');
}

