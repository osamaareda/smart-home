/* 
 * File:   buzzer.c
 * Author: osama reda
 *
 * Created on September 17, 2023, 08:15 PM
 */

#include"buzzer.h"
/**
 * @brief  : initialize buzzer to be output and off
 * @param  : buzzer -> pointer to (buzzer_config_t) structure @ref buzzer_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if BUZZER_CONFIG==ENABLE
Std_ReturnType buzzer_init(buzzer_config_t *buzzer){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==buzzer){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_output_low_init(&(buzzer->buzzer_pin));
        buzzer->buzzer_state=buzzer->buzzer_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : turn the buzzer on
 * @param  : buzzer -> pointer to (buzzer_config_t) structure @ref buzzer_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if BUZZER_CONFIG==ENABLE
Std_ReturnType buzzer_on(buzzer_config_t *buzzer){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==buzzer){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_logic_write(&(buzzer->buzzer_pin),HIGH);
        buzzer->buzzer_state=buzzer->buzzer_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : turn the buzzer off
 * @param  : buzzer -> pointer to (buzzer_config_t) structure @ref buzzer_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if BUZZER_CONFIG==ENABLE
Std_ReturnType buzzer_off(buzzer_config_t *buzzer){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==buzzer){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_logic_write(&(buzzer->buzzer_pin),LOW);
        buzzer->buzzer_state=buzzer->buzzer_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : toggle the buzzer 
 * @param  : buzzer -> pointer to (buzzer_config_t) structure @ref buzzer_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if BUZZER_CONFIG==ENABLE
Std_ReturnType buzzer_toggle(buzzer_config_t *buzzer){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==buzzer){
        ret=E_NOT_OK;
    } 
    else{
        gpio_ret=gpio_pin_toggle_logic(&(buzzer->buzzer_pin));
        ret=E_OK;
    }
    
    return ret;
}
#endif
