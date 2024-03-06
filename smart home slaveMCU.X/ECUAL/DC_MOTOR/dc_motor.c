/* 
 * File:   dc_motor.c
 * Author: osama reda
 *
 * Created on September 22, 2023, 8:26 PM
 */
#include"dc_motor.h"
/**
 * @brief  : initialize DC motor to be output and off
 * @param  : dc_motor -> pointer to (dc_motor_config_t) structure @ref dc_motor_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if DC_MOTOR_CONFIG==ENABLE
Std_ReturnType dc_motor_init(dc_motor_config_t *dc_motor){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==dc_motor){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_output_low_init(&(dc_motor->dc_motor_pin0));
        gpio_ret=gpio_pin_output_low_init(&(dc_motor->dc_motor_pin1));
        dc_motor->dc_motor_state=DC_MOTOR_OFF;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : move DC motor right
 * @param  : dc_motor -> pointer to (dc_motor_config_t) structure @ref dc_motor_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if DC_MOTOR_CONFIG==ENABLE
Std_ReturnType dc_motor_move_right(dc_motor_config_t *dc_motor){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==dc_motor){
        ret=E_NOT_OK;
    }
    else{      
        gpio_ret =gpio_pin_logic_write(&(dc_motor->dc_motor_pin0),HIGH);
        gpio_ret =gpio_pin_logic_write(&(dc_motor->dc_motor_pin1),LOW);
        dc_motor->dc_motor_state=DC_MOTOR_ON;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : move DC motor left
 * @param  : dc_motor -> pointer to (dc_motor_config_t) structure @ref dc_motor_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if DC_MOTOR_CONFIG==ENABLE
Std_ReturnType dc_motor_move_left(dc_motor_config_t *dc_motor){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==dc_motor){
        ret=E_NOT_OK;
    }
    else{      
        gpio_ret =gpio_pin_logic_write(&(dc_motor->dc_motor_pin0),LOW);
        gpio_ret =gpio_pin_logic_write(&(dc_motor->dc_motor_pin1),HIGH);
        dc_motor->dc_motor_state=DC_MOTOR_ON;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : stop DC motor 
 * @param  : dc_motor -> pointer to (dc_motor_config_t) structure @ref dc_motor_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if DC_MOTOR_CONFIG==ENABLE
Std_ReturnType dc_motor_stop(dc_motor_config_t *dc_motor){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==dc_motor){
        ret=E_NOT_OK;
    }
    else{      
        gpio_ret =gpio_pin_logic_write(&(dc_motor->dc_motor_pin0),LOW);
        gpio_ret =gpio_pin_logic_write(&(dc_motor->dc_motor_pin1),LOW);
        dc_motor->dc_motor_state=DC_MOTOR_OFF;
        ret=E_OK;
    }
    
    return ret;
}
#endif