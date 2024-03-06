/* 
 * File:   relay.c
 * Author: osama reda
 * 
 * Created on September 11, 2023, 11:22 PM
 */

#ifndef RELAY_H
#define	RELAY_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_relay_cfg.h"

/*---------------data type declaration---------------*/
typedef enum{
    RELAY_OFF,
    RELAY_ON
}relay_state_t;

typedef struct{
    pin_config_t relay_pin;      /* @ref  pin_config_t */
    relay_state_t relay_state;   /* @ref  relay_state_t */
}relay_config_t;

/*----------------function declaration-----------------*/
Std_ReturnType relay_init(relay_config_t *relay);
Std_ReturnType relay_on(relay_config_t *relay);
Std_ReturnType relay_off(relay_config_t *relay);
Std_ReturnType relay_toggle(relay_config_t *relay);
#endif	/* RELAY_H */