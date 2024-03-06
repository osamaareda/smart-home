/* 
 * File:   dc_motor.h
 * Author: osama reda
 *
 * Created on September 22, 2023, 8:26 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_dc_motor_cfg.h"

/*---------------data type declaration---------------*/
typedef enum{
    DC_MOTOR_OFF,
    DC_MOTOR_ON
}dc_motor_state_t;

typedef struct{
    pin_config_t dc_motor_pin0;        /* @ref  pin_config_t */
    pin_config_t dc_motor_pin1;        /* @ref  pin_config_t */
    dc_motor_state_t dc_motor_state;   /* @ref  relay_state_t */
}dc_motor_config_t;

/*----------------function declaration-----------------*/
Std_ReturnType dc_motor_init(dc_motor_config_t *dc_motor);
Std_ReturnType dc_motor_move_right(dc_motor_config_t *dc_motor);
Std_ReturnType dc_motor_move_left(dc_motor_config_t *dc_motor);
Std_ReturnType dc_motor_stop(dc_motor_config_t *dc_motor);
#endif	/* DC_MOTOR_H */