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

/*
 * Initialitation for Pin Input.
 */
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

/*
 * Initialization for data stored for status peripheral
 */
void periphInit(pheripheral_typedef* Pheripheral, int pheripheralAmount)
{
	for(int i=1; i<=pheripheralAmount; i++) {
		Pheripheral[i].id = i;
		Pheripheral[i].state = 0;
	}
}

/*
 * for reading input
 */
void readInput(pheripheral_typedef* Pheripheral)
{
	// baca inputan
	Pheripheral[10].state = GPIO_ReadInputDataBit(INPUT_PH1_PORT, BLINK_PIN_MASK(INPUT_PH1_PIN) );
	Pheripheral[11].state = GPIO_ReadInputDataBit(INPUT_PH2_PORT, BLINK_PIN_MASK(INPUT_PH2_PIN) );
	Pheripheral[12].state = GPIO_ReadInputDataBit(INPUT_PH3_PORT, BLINK_PIN_MASK(INPUT_PH3_PIN) );
	Pheripheral[13].state = GPIO_ReadInputDataBit(INPUT_PH4_PORT, BLINK_PIN_MASK(INPUT_PH4_PIN) );
	Pheripheral[14].state = GPIO_ReadInputDataBit(INPUT_PH5_PORT, BLINK_PIN_MASK(INPUT_PH5_PIN) );
	Pheripheral[15].state = GPIO_ReadInputDataBit(INPUT_PH6_PORT, BLINK_PIN_MASK(INPUT_PH6_PIN) );
	Pheripheral[16].state = GPIO_ReadInputDataBit(INPUT_PH7_PORT, BLINK_PIN_MASK(INPUT_PH7_PIN) );
	Pheripheral[17].state = GPIO_ReadInputDataBit(INPUT_PH8_PORT, BLINK_PIN_MASK(INPUT_PH8_PIN) );
	Pheripheral[18].state = GPIO_ReadInputDataBit(INPUT_PH9_PORT, BLINK_PIN_MASK(INPUT_PH9_PIN) );
	Pheripheral[19].state = GPIO_ReadInputDataBit(INPUT_PH10_PORT, BLINK_PIN_MASK(INPUT_PH10_PIN) );
	Pheripheral[20].state = GPIO_ReadInputDataBit(INPUT_PH11_PORT, BLINK_PIN_MASK(INPUT_PH11_PIN) );
	Pheripheral[21].state = GPIO_ReadInputDataBit(INPUT_PH12_PORT, BLINK_PIN_MASK(INPUT_PH12_PIN) );
}

/*
 * writing output
 */
void writeOutput(short PheriphID, short PheriphState)
{

	if(PheriphState == 0) {
	switch (PheriphID) {
	case 1:
		GPIO_ResetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN1) );
		break;
	case 2:
		GPIO_ResetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN2) );
		break;
	case 3:
		GPIO_ResetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN3) );
		break;

	case 4:
		GPIO_ResetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN4) );
		break;
	case 5:
		GPIO_ResetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN5) );
		break;
	case 6:
		GPIO_ResetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN6) );
		break;

	case 7:
		GPIO_ResetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN7) );
		break;
	case 8:
		GPIO_ResetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN8) );
		break;
	case 9:
		GPIO_ResetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN9) );
	}
	} else	if(PheriphState == 1) {
	switch (PheriphID) {
	case 1:
		GPIO_SetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN1) );
		break;
	case 2:
		GPIO_SetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN2) );
		break;
	case 3:
		GPIO_SetBits( OUTPUT_PORT1_3, BLINK_PIN_MASK(OUTPUT_PIN3) );
		break;

	case 4:
		GPIO_SetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN4) );
		break;
	case 5:
		GPIO_SetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN5) );
		break;
	case 6:
		GPIO_SetBits( OUTPUT_PORT4_6, BLINK_PIN_MASK(OUTPUT_PIN6) );
		break;

	case 7:
		GPIO_SetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN7) );
		break;
	case 8:
		GPIO_SetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN8) );
		break;
	case 9:
		GPIO_SetBits( OUTPUT_PORT7_9, BLINK_PIN_MASK(OUTPUT_PIN9) );
	}
	}
}
