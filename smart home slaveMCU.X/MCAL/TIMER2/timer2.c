/* 
 * File:   timer2.c
 * Author: osama reda
 *
 * Created on December 6, 2023, 1:47 AM
 */

#include "timer2.h"

/* Pointer to function to hold the callbacks func for TIMER2 */
#if TIMER0_INTERRUPT_FEATURE==ENABLE
    static void (*TMR2_InterruptHandler)(void) = NULL;
#endif
static uint8 timer2_preload = 0;

/**
 * @brief :Initializes TIMER2
 * @Description :This routine initializes TIMER2.
 *               This routine must be called before any other TIMER1 routine is called.
 *               This routine should only be called once during system initialization.
 * @param : _timer -> pointer to (timer2_config_t) TIMER1 configurations structure @ref timer2_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER2_CONFIG==ENABLE
Std_ReturnType Timer2_Init(const timer2_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER0 */
        TIMER2_MODULE_DISABLE();
        /* Configure the Prescaler for TIMER2 */
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        /* Configure the Postscaler for TIMER2 */
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        /*set preload value */
        TMR2 = _timer->timer2_preload_value;
        timer2_preload = _timer->timer2_preload_value;
        /* Configure the interrupt  */        
        #if TIMER2_INTERRUPT_FEATURE==ENABLE
        TIMER2_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS==ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(HIGH_PRIORITY == _timer->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER2_HighPrioritySet();
        }
        else if(LOW_PRIORITY == _timer->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER2_LowPrioritySet();
        }
        #elif INTERRUPT_PRIORITY_LEVELS==DISABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER2_InterruptEnable();
        TMR2_InterruptHandler=_timer->TMR2_InterruptHandler;
        #endif

        /* Enable the TIMER0 */
        TIMER2_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :deinitializes TIMER2
 * @param : _timer -> pointer to (timer2_config_t) TIMER1 configurations structure @ref timer2_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER2_CONFIG==ENABLE
Std_ReturnType Timer2_DeInit(const timer2_config_t *_timer){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER0 */
        TIMER2_MODULE_DISABLE();
        /* Disable  TIMER0 interrupt*/
        #if TIMER2_INTERRUPT_FEATURE==ENABLE
        TIMER2_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :Write value on TIMER2 registers TMR2
 * @Preconditions :Timer2_Init() function should have been called before calling this function.
 * @param : _timer -> pointer to (timer2_config_t) TIMER1 configurations structure @ref timer2_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER2_CONFIG==ENABLE
Std_ReturnType Timer2_Write_Value(const timer2_config_t *_timer, uint8 _value){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = _value;
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :read value from TIMER1 registers TMR2
 * @Preconditions :Timer2_Init() function should have been called before calling this function.
 * @param : _timer -> pointer to (timer2_config_t) TIMER1 configurations structure @ref timer2_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER2_CONFIG==ENABLE
Std_ReturnType Timer2_Read_Value(const timer2_config_t *_timer, uint8 *_value){
    
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        *_value = TMR2;
        ret = E_OK;
    }
    return ret;
}
#endif


/*
 * Internal Interrupt TIMER2 MCAL Helper function 
 */
void TMR2_ISR(void){
    //clear TIMER2 interrupt flag
    TIMER2_InterruptFlagClear();
    //restore prescaler value
    TMR2 = timer2_preload;
    //Application Callback function gets called every time this ISR executes
    if(TMR2_InterruptHandler){TMR2_InterruptHandler();}
}