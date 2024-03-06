/* 
 * File:   init.h
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */

#ifndef INIT_H
#define	INIT_H
/*-------------------includes---------------------*/
#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include "interrupt_manager.h"
#include "i2c_slave.h"
#include "../ECUAL/LED/led.h"
#include "../ECUAL/DC_MOTOR/dc_motor.h"
#include "../ECUAL/7_SEGMENT/seven_segment.h"
#include "../MCAL/CCP/hal_ccp.h"
#include "../MCAL/TIMER2/timer2.h"
#include "../MCAL/INTERRUPT/mcal_external_interrupt.h"
#include "../MCAL/USART/usart.h"

/*--------------function declaration--------------*/
void Initialize(void);
void MY_EUSART_RX_ISR(void);

/*--------------------externs---------------------*/
extern led_config_t led_red;
extern led_config_t led_blue;
extern interrupt_INTx_t MY_INT0;
extern dc_motor_config_t motor1;
extern dc_motor_config_t motor2;
extern seven_segment_config_t seg_1;
extern seven_segment_config_t seg_2;
extern ccp_t ccp1;
extern timer2_config_t timer2;

#endif	/* INIT_H */