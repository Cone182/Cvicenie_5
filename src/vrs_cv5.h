/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: zolta
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_


void startupNVIC();
void adc_init(void);
void startupUSART();
void blikaj();
void uloha_1();
void sendZnak(volatile int uart, volatile int hodnota);

#endif /* VRS_CV5_H_ */
