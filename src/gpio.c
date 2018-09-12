/*
 * gpio.c
 *
 *  Created on: Sep 11, 2018
 *      Author: otm3
 */
#include "platform_config.h"
#include "BlinkLed.h"

void outputInit()
{
	// Enable GPIO Peripheral clock
	// Port numbers: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
	RCC_APB2PeriphClockCmd(BLINK_RCC_MASKx(0), ENABLE);
	RCC_APB2PeriphClockCmd(BLINK_RCC_MASKx(1), ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pin in output push/pull mode
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(OUTPUT_PIN1)| BLINK_PIN_MASK(OUTPUT_PIN2)| BLINK_PIN_MASK(OUTPUT_PIN3);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(OUTPUT_PORT1_3, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(OUTPUT_PIN4)| BLINK_PIN_MASK(OUTPUT_PIN5)| BLINK_PIN_MASK(OUTPUT_PIN6);
	GPIO_Init(OUTPUT_PORT4_6, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(OUTPUT_PIN7)| BLINK_PIN_MASK(OUTPUT_PIN8)| BLINK_PIN_MASK(OUTPUT_PIN9);
	GPIO_Init(OUTPUT_PORT7_9, &GPIO_InitStructure);

	// Start with Pheripheral turned off
	GPIO_ResetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN1) );
	GPIO_ResetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN2) );
	GPIO_ResetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN3) );

	GPIO_ResetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN4) );
	GPIO_ResetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN5) );
	GPIO_ResetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN6) );

	GPIO_ResetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN7) );
	GPIO_ResetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN8) );
	GPIO_ResetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN9) );
}


void inputInit()
{
	// Enable GPIO Peripheral clock
	// Port numbers: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
	RCC_APB2PeriphClockCmd(BLINK_RCC_MASKx(0), ENABLE);
	RCC_APB2PeriphClockCmd(BLINK_RCC_MASKx(1), ENABLE);
	RCC_APB2PeriphClockCmd(BLINK_RCC_MASKx(2), ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pin in output push/pull mode
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH1_PIN);
	GPIO_Init(INPUT_PH1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH2_PIN);
	GPIO_Init(INPUT_PH2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH3_PIN);
	GPIO_Init(INPUT_PH3_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH4_PIN);
	GPIO_Init(INPUT_PH4_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH5_PIN);
	GPIO_Init(INPUT_PH5_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH6_PIN);
	GPIO_Init(INPUT_PH6_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH7_PIN);
	GPIO_Init(INPUT_PH7_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH8_PIN);
	GPIO_Init(INPUT_PH8_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH9_PIN);
	GPIO_Init(INPUT_PH9_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH10_PIN);
	GPIO_Init(INPUT_PH10_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH11_PIN);
	GPIO_Init(INPUT_PH11_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(INPUT_PH12_PIN);
	GPIO_Init(INPUT_PH12_PORT, &GPIO_InitStructure);
}

void periphInit(pheripheral_typedef* Pheripheral, int pheripheralAmount)
{
	for(int i=1; i<=pheripheralAmount; i++) {
		Pheripheral[i].id = i;
		Pheripheral[i].state = 0;
	}
}
void readInput()
{
	// baca inputan
}

void writeOutput()
{
	// kirim Outputan
}
