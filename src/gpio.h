/*
 * gpio.h
 *
 *  Created on: Sep 11, 2018
 *      Author: otm3
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "platform_config.h"

void outputInit();
void inputInit();
void periphInit(pheripheral_typedef* Pheripheral, int pheripheralAmount);

#endif /* GPIO_H_ */
