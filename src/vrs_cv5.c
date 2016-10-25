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
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn; // nam prerušení nájdete v súbore stm32l1xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void startupUSART(){
	GPIO_InitTypeDef gpioInitStruc; //RX
	GPIO_InitTypeDef gpioInitStruc2; //TX
	USART_InitTypeDef usartInitStruc;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	gpioInitStruc.GPIO_Mode = GPIO_Mode_AF;
	gpioInitStruc.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruc.GPIO_Pin = GPIO_Pin_2;
	gpioInitStruc.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &gpioInitStruc);

	gpioInitStruc2.GPIO_Mode = GPIO_Mode_AF;
	gpioInitStruc2.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruc2.GPIO_Pin = GPIO_Pin_3;
	gpioInitStruc2.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &gpioInitStruc2);

	usartInitStruc.USART_BaudRate = 2*9600;
	usartInitStruc.USART_WordLength = USART_WordLength_8b;
	usartInitStruc.USART_StopBits = USART_StopBits_1;
	usartInitStruc.USART_Parity = USART_Parity_No;
	usartInitStruc.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInitStruc.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &usartInitStruc);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = USART2_IRQn; // nam prerušení nájdete v súbore stm32l1xx.h
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART2, ENABLE);
}

void adc_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  /* Configure ADCx Channel 2 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Enable the HSI oscillator */
  RCC_HSICmd(ENABLE);
  /* Check that HSI oscillator is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  /* Enable ADC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  /* ADC1 configuration */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  /* ADCx regular channel8 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_96Cycles);
  /* Enable the ADC */
  ADC_Cmd(ADC1, ENABLE);

  /* Wait until the ADC1 is ready */
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }
  /* Start ADC Software Conversion */
  ADC_SoftwareStartConv(ADC1);
}

/*void ADC1_IRQHandler(void){
	blikaj();
	ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}*/

void blikaj(){
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
	uint16_t AD_value;

	AD_value=ADC_GetConversionValue(ADC1);

	if ((AD_value>1995) && (AD_value<2035)){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (int c=1; c<= 200; c++){
			for (int d=1; d<= 200; d++)
			{}
		}
	}
	else if ((AD_value>2885) && (AD_value<2925)){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (int c=1; c<= 400; c++){
			for (int d=1; d<= 400; d++)
			{}
		}
	}
	else if ((AD_value>3440) && (AD_value<3480)){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (int c=1; c<= 600; c++){
			for (int d=1; d<= 600; d++)
			{}
		}
	}
	else if ((AD_value>3640) && (AD_value<3680)){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (int c=1; c<= 800; c++){
			for (int d=1; d<= 800; d++)
			{}
		}
	}
	else if ((AD_value>3925) && (AD_value<3965)){
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
}

void uloha_1(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitStruc;
	gpioInitStruc.GPIO_Mode = GPIO_Mode_OUT;
	gpioInitStruc.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc.GPIO_PuPd = GPIO_PuPd_UP;
	gpioInitStruc.GPIO_Pin = GPIO_Pin_5;
	gpioInitStruc.GPIO_Speed = GPIO_Speed_40MHz;

	GPIO_Init(GPIOA, &gpioInitStruc);

	ADC_SoftwareStartConv(ADC1);
}

void sendRetaz(char c[],int dlzka) {
	for(int i=0;i<dlzka;i++){
		USART_SendData(USART2, (uint8_t) c[i]);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
}
