/* 
 * File:   button.h
 * Author: osama reda
 *
 * Created on September 18, 2023, 06:00 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_button_cfg.h"
/*---------------data type declaration---------------*/
typedef enum{
    BUTTON_NOT_PUSHED,
    BUTTON_PUSHED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
}button_connection_t;

typedef struct{
    pin_config_t button_pin;                /* @ref  pin_config_t */
    button_state_t button_state;            /* @ref  button_state_t */
    button_connection_t button_connection;  /* @ref  button_connection_t */
}button_config_t;

/*----------------function declaration-----------------*/
Std_ReturnType button_init(button_config_t *button);
Std_ReturnType button_read(button_config_t *button, button_state_t *button_state);
#endif	/* BUTTON_H */