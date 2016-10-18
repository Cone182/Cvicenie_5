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

}




