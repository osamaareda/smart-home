/* 
 * File:   init.h
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */

#ifndef INIT_H
#define	INIT_H

/*-------------------includes---------------------*/
#include "device_config.h"
#include "../mcc_generated_files/examples/i2c_master_example.h"
#include "../ECUAL/LCD/lcd.h"
#include "../ECUAL/buzzer/buzzer.h"
#include "../ECUAL/RealTimeClockDS1307/RealTimeClockDS1307.h"
#include "../MCAL/INTERRUPT/mcal_external_interrupt.h"
#include "../MCAL/ADC/adc.h"
#include "../MCAL/USART/usart.h"
/*--------------function declaration--------------*/
void _Initialize(void);
void APP_INT0_ISR(void);
void APP_INT1_ISR(void);
void APP_INT2_ISR(void);
void MY_ADC_ISR(void);

/*--------------------externs---------------------*/
extern lcd_config_t lcd;
extern interrupt_INTx_t MY_INT0;
extern interrupt_INTx_t MY_INT1;
extern interrupt_INTx_t MY_INT2;
extern buzzer_config_t buzzer;
extern adc_config_t adc;
extern usart_config_t uart;
#endif	/* INIT_H */
