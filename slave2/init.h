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
#include "../ECUAL/RELAY/relay.h"
#include "../ECUAL/DC_MOTOR/dc_motor.h"
#include "../ECUAL/LCD/lcd.h"
#include "../ECUAL/KEYPAD/keypad.h"
#include "../ECUAL/7_SEGMENT/seven_segment.h"
#include "../MCAL/CCP/hal_ccp.h"
#include "../MCAL/TIMER0/timer0.h"
#include "../MCAL/TIMER2/timer2.h"
#include "../MCAL/EEPROM/eeprom.h"
#include "../MCAL/INTERRUPT/mcal_external_interrupt.h"
#include "../MCAL/INTERRUPT/mcal_internal_interrupt.h"
#include "../MCAL/USART/usart.h"


/*--------------function declaration--------------*/
void Initialize(void);
void APP_INT0_ISR(void);
void APP_INT1_ISR(void);
void APP_INT2_ISR(void);
void APP_RB0_ISR(void);
void APP_RB1_ISR(void);
void APP_RB2_ISR(void);
void MY_TMR0_ISR(void);

/*--------------------externs---------------------*/
extern usart_config_t uart;
extern led_config_t led_yellow;
extern led_config_t led_1;
extern led_config_t led_2;
extern led_config_t led_3;
extern led_config_t led_4;
extern relay_config_t relay;
extern interrupt_INTx_t MY_INT0;
extern interrupt_INTx_t MY_INT1;
extern interrupt_INTx_t MY_INT2;
extern interrupt_RBx_t MY_RB0;
extern interrupt_RBx_t MY_RB1;
extern timer0_config_t timer0;
extern dc_motor_config_t door_motor;
extern lcd_config_t lcd;
extern keypad_config_t keypad;
#endif	/* INIT_H */
