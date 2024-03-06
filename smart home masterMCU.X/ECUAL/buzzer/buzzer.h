/* 
 * File:   buzzer.h
 * Author: 20128
 *
 * Created on February 24, 2024, 1:10 PM
 */

#ifndef BUZZER_H
#define	BUZZER_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_buzzer_cfg.h"

/*---------------data type declaration---------------*/
typedef enum{
    LED_OFF,
    LED_ON
}buzzer_status_t;

typedef struct{
    pin_config_t buzzer_pin;   /* @ref  pin_config_t */
    buzzer_status_t buzzer_state; /* @ref  led_status_t */
}buzzer_config_t;

/*----------------function declaration-----------------*/
Std_ReturnType buzzer_init(buzzer_config_t *led);
Std_ReturnType buzzer_on(buzzer_config_t *led);
Std_ReturnType buzzer_off(buzzer_config_t *led);
Std_ReturnType buzzer_toggle(buzzer_config_t *led);

#endif	/* BUZZER_H */

