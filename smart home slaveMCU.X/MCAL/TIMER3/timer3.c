/* 
 * File:   timer3.c
 * Author: osama reda
 *
 * Created on December 6, 2023, 4:38 AM
 */

#include"timer3.h"

/* Pointer to function to hold the callbacks func for TIMER3 */
#if TIMER3_INTERRUPT_FEATURE==ENABLE
    static void (*TMR3_InterruptHandler)(void) = NULL;
#endif
static uint16 timer3_preload = 0;

/* helper function to initialize ADC interrupt */
static inline void Timer3_Mode_Select(const timer3_config_t *_timer);
static inline void timer3_reg_wr_mode_Select(const timer3_config_t *_timer);

/**
 * @brief :Initializes TIMER1
 * @Description :This routine initializes TIMER1.
 *               This routine must be called before any other TIMER1 routine is called.
 *               This routine should only be called once during system initialization.
 * @param : _timer -> pointer to (timer1_config_t) TIMER1 configurations structure @ref timer1_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER3_CONFIG==ENABLE
Std_ReturnType Timer3_Init(const timer3_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER1 */
        TIMER3_MODULE_DISABLE();
        /* Configure the Prescaler for TIMER1 */
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
         /* select the mode for TIMER1 */
        Timer3_Mode_Select(_timer);
        /* select timer1_reg_wr_mode 16 or 8bit*/
        timer3_reg_wr_mode_Select(_timer);
        /*set preload value */
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
        /* Configure the interrupt  */        
        #if TIMER3_INTERRUPT_FEATURE==ENABLE
        TIMER3_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS==ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(HIGH_PRIORITY == _timer->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER3_HighPrioritySet();
        }
        else if(LOW_PRIORITY == _timer->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_LowPrioritySet();
        }
        #elif INTERRUPT_PRIORITY_LEVELS==DISABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER3_InterruptEnable();
        TMR3_InterruptHandler=_timer->TMR3_InterruptHandler;
        #endif

        /* Enable the TIMER1 */
        TIMER3_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :deinitializes TIMER1
 * @param : _timer -> pointer to (timer1_config_t) TIMER1 configurations structure @ref timer1_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER3_CONFIG==ENABLE
Std_ReturnType Timer3_DeInit(const timer3_config_t *_timer){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER0 */
        TIMER3_MODULE_DISABLE();
        /* Disable  TIMER0 interrupt*/
        #if TIMER1_INTERRUPT_FEATURE==ENABLE
        TIMER3_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :Write value on TIMER1 registers TMR1L and TMR1H
 * @Preconditions :Timer1_Init() function should have been called before calling this function.
 * @param : _timer -> pointer to (timer1_config_t) TIMER1 configurations structure @ref timer1_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER3_CONFIG==ENABLE
Std_ReturnType Timer3_Write_Value(const timer3_config_t *_timer, uint16 _value){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :read value from TIMER1 registers TMR1L and TMR1H
 * @Preconditions :Timer1_Init() function should have been called before calling this function.
 * @param : _timer -> pointer to (timer1_config_t) TIMER1 configurations structure @ref timer1_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER3_CONFIG==ENABLE
Std_ReturnType Timer3_Read_Value(const timer3_config_t *_timer, uint16 *_value){
    
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_value = 0, h_value = 0;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        l_value = TMR3L;
        h_value = TMR3H;
        *_value = (uint16)((h_value << 8) + l_value);
        ret = E_OK;
    }
    return ret;
}
#endif


static inline void Timer3_Mode_Select(const timer3_config_t *_timer){
    if(TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
    }
}

static inline void timer3_reg_wr_mode_Select(const timer3_config_t *_timer){
    if(TIMER3_RW_REG_16Bit_MODE == _timer->timer3_reg_wr_mode){
        TIMER3_RW_REG_16BIT_MODE_ENABLE();
    }
    else if(TIMER3_RW_REG_8Bit_MODE == _timer->timer3_reg_wr_mode){
        TIMER3_RW_REG_8BIT_MODE_ENABLE();
    }
}


/*
 * Internal Interrupt TIMER1 MCAL Helper function 
 */
void TMR3_ISR(void){
    //clear TIMER3 interrupt flag
    TIMER3_InterruptFlagClear();
    //restore prescaler value
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);
    //Application Callback function gets called every time this ISR executes
    if(TMR3_InterruptHandler){TMR3_InterruptHandler();}
}