/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"
#include "uart.h"
#include "platform_config.h"
#include "codec2_fifo.h"
#include "gpio.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 led blink sample (trace via NONE).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//
// The external clock frequency is specified as a preprocessor definition
// passed to the compiler via a command line option (see the 'C/C++ General' ->
// 'Paths and Symbols' -> the 'Symbols' tab, if you want to change it).
// The value selected during project creation was HSE_VALUE=8000000.
//
// Note: The default clock settings take the user defined HSE_VALUE and try
// to reach the maximum possible system clock. For the default 8 MHz input
// the result is guaranteed, but for other values it might not be possible,
// so please adjust the PLL settings in system/src/cmsis/system_stm32f10x.c
//

// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 1 / 100)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#define LENGTHRpiRx 128

volatile uint8_t status1 = 0;
volatile struct FIFO *rxDatarPi;

int
main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %u Hz\n", SystemCoreClock);

  timer_start(); // configuring timer using systick

  uint32_t seconds = 0;

  USART_InitTypeDef USART_InitStructure;
  initUART(&USART_InitStructure);
  USART_SendString(USARTrPi, "SmartHome Started v0.2 \n\r");
  rxDatarPi = fifo_create(LENGTHRpiRx);
  pheripheral_typedef Pheripheral[PHERIPHERAL_AMOUNT];
  periphInit(Pheripheral, PHERIPHERAL_AMOUNT);
  if (SysTick_Config(SystemCoreClock / 1000))
  {
    /* Capture error */
    while (1);
  }

  // Infinite loop
  while (1)
    {
//	  USART_Tx(USARTrPi, Data);
	  if( (status1 & S1DATA) == S1DATA) {

			char idNumChar[4], idStateChar[4], tempChar[10];
			//short temp;

			fifo_read(rxDatarPi, tempChar, 9);
			/*
			fifo_read(rxDatarPi, &temp, 1); // ditch "S" header
			fifo_read(rxDatarPi, idNumChar, 3); // copy value id consist 3 char
			*/
			strncpy(idNumChar, &(tempChar[1]), 3);
			idNumChar[3] = '\0';
			int idNumInt = atoi(idNumChar);

			/*
			fifo_read(rxDatarPi, &temp, 1);	// ditch "&" separator
			fifo_read(rxDatarPi, idStateChar, 3); // copy state consist 3 char
			*/
			strncpy(idStateChar, &(tempChar[5]), 3);
			idStateChar[3] = '\0';
			int idStateInt = atoi(idStateChar);
			//fifo_read(rxDatarPi, &temp, 1);	// ditch "E" tail

			//USART_SendString(USARTrPi, 'S');
			USART_SendString(USARTrPi, idNumChar);
			USART_SendString(USARTrPi, idStateChar);

			if( (idNumInt > 0) && (idNumInt <= PHERIPHERAL_AMOUNT) ) {
				Pheripheral[idNumInt].id = idNumInt;
				Pheripheral[idNumInt].state = idStateInt;
			} else {
				printPheripheral(Pheripheral);
			}
			//retVal = idNumInt;

		  // reset status data available
		  status1 &= ~S1DATA;
	  }

    }
  // Infinite loop, never return.
}


#pragma GCC diagnostic pop

// read if received data already hit one frame
// package example Sxxx&xxxE

// ----------------------------------------------------------------------------
