/* 
 * File:   app.c
 * Author: osama reda
 * 
 * Created on September 11, 2023, 11:22 PM
 */
 
#include"relay.h"
/**
 * @brief  : initialize relay to be output and off
 * @param  : relay -> pointer to (relay_config_t) structure @ref relay_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if RELAY_CONFIG==ENABLE
Std_ReturnType relay_init(relay_config_t *relay){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==relay){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_output_low_init(&(relay->relay_pin));
        relay->relay_state=relay->relay_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : turn the relay on
 * @param  : relay -> pointer to (relay_config_t) structure @ref relay_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if RELAY_CONFIG==ENABLE
Std_ReturnType relay_on(relay_config_t *relay){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==relay){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret =gpio_pin_logic_write(&(relay->relay_pin),HIGH);
        relay->relay_state=relay->relay_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : turn the relay off
 * @param  : relay -> pointer to (relay_config_t) structure @ref relay_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if RELAY_CONFIG==ENABLE
Std_ReturnType relay_off(relay_config_t *relay){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==relay){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret =gpio_pin_logic_write(&(relay->relay_pin),LOW);
        relay->relay_state=relay->relay_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif

/**
 * @brief  : toggle the relay 
 * @param  : relay -> pointer to (relay_config_t) structure @ref relay_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if RELAY_CONFIG==ENABLE
Std_ReturnType relay_toggle(relay_config_t *relay){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==relay){
        ret=E_NOT_OK;
    } 
    else{
        gpio_ret=gpio_pin_toggle_logic(&(relay->relay_pin));
        ret=E_OK;
    }
    
    return ret;
}
#endif