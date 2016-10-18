/*
 * vrs_cv5.c
 *
 *  Created on: 18. 10. 2016
 *      Author: zolta
 */

#include "stm32l1xx.h"
#include "vrs_cv5.h"


void startupNVIC(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn; //zoznam prerušení nájdete v súbore stm32l1xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	ADC_ITConfig(ADC1,ADC_IT_OVR,ENABLE);

	ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC);
	ADC_GetFlagStatus(ADC1, ADC_FLAG_OVR);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitStruc; //RX
	gpioInitStruc.GPIO_Mode = GPIO_Mode_AF;
	gpioInitStruc.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruc.GPIO_Pin = GPIO_Pin_9;
	gpioInitStruc.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &gpioInitStruc);

	GPIO_InitTypeDef gpioInitStruc2; //TX
	gpioInitStruc2.GPIO_Mode = GPIO_Mode_AF;
	gpioInitStruc2.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruc2.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruc2.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &gpioInitStruc2);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitTypeDef usartInitStruc;
	usartInitStruc.USART_BaudRate = 9600;
	usartInitStruc.USART_WordLength = USART_WordLength_8b;
	usartInitStruc.USART_StopBits = USART_StopBits_1;
	usartInitStruc.USART_Parity = USART_Parity_No;
	usartInitStruc.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInitStruc.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &usartInitStruc);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);














}




