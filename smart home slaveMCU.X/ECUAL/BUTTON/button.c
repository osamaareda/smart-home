/* 
 * File:   button.c
 * Author: osama reda
 *
 * Created on September 18, 2023, 06:00 AM
 */
#include"button.h"
/**
 * @brief  : initialize button to be input and low
 * @param  : button -> pointer to (button_config_t) structure @ref button_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if BUTTON_CONFIG==ENABLE
Std_ReturnType button_init(button_config_t *button){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==button){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_input_init(&(button->button_pin));
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : read button status
 * @param  : button -> pointer to (button_config_t) structure @ref button_config_t
 * @param  : btn_s -> pointer to (button_status) enum @ref button_status
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if BUTTON_CONFIG==ENABLE
Std_ReturnType button_read(button_config_t *button, button_state_t *button_state){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    logic_t button_logic=LOW;
    if(NULL==button || NULL==button_state){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_logic_read(&(button->button_pin),&button_logic);
        if(BUTTON_ACTIVE_HIGH==(button->button_connection)){
            if(HIGH==button_logic){
                *button_state=BUTTON_PUSHED;
                button->button_state=BUTTON_PUSHED;
            }
            else {
                *button_state=BUTTON_NOT_PUSHED;
                button->button_state=BUTTON_NOT_PUSHED;
            }
        }
        else if(BUTTON_ACTIVE_LOW==(button->button_connection)){
            if(LOW==button_logic){
                *button_state=BUTTON_PUSHED;
                button->button_state=BUTTON_PUSHED;
            }
            else {
                *button_state=BUTTON_NOT_PUSHED;
                button->button_state=BUTTON_NOT_PUSHED;
            }
        }
        
    }
    
    return ret;
}
#endif