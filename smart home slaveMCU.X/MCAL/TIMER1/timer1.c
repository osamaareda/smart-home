/* 
 * File:   timer1.c
 * Author: osama reda
 *
 * Created on October 30, 2023, 9:13 PM
 */

#include "timer1.h"

/* Pointer to function to hold the callbacks func for TIMER1 */
#if TIMER1_INTERRUPT_FEATURE==ENABLE
    static void (*TMR1_InterruptHandler)(void) = NULL;
#endif
static uint16 timer1_preload = 0;

/* helper function to initialize ADC interrupt */
static inline void Timer1_Mode_Select(const timer1_config_t *_timer);
static inline void timer1_reg_wr_mode_Select(const timer1_config_t *_timer);
static inline void TIMER1_OSC_HW_select(const timer1_config_t *_timer);

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
#if TIMER1_CONFIG==ENABLE
Std_ReturnType Timer1_Init(const timer1_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER1 */
        TIMER1_MODULE_DISABLE();
        /* Configure the Prescaler for TIMER1 */
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
         /* select the mode for TIMER1 */
        Timer1_Mode_Select(_timer);
        /* select timer1_reg_wr_mode 16 or 8bit*/
        timer1_reg_wr_mode_Select(_timer);
        /*TIMER1 OSC HW ENABLE*/
        TIMER1_OSC_HW_select(_timer);
        /*set preload value */
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;
        /* Configure the interrupt  */        
        #if TIMER1_INTERRUPT_FEATURE==ENABLE
        TIMER1_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS==ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(HIGH_PRIORITY == _timer->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_HighPrioritySet();
        }
        else if(LOW_PRIORITY == _timer->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet();
        }
        #elif INTERRUPT_PRIORITY_LEVELS==DISABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER1_InterruptEnable();
        TMR1_InterruptHandler=_timer->TMR1_InterruptHandler;
        #endif

        /* Enable the TIMER1 */
        TIMER1_MODULE_ENABLE();
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
#if TIMER1_CONFIG==ENABLE
Std_ReturnType Timer1_DeInit(const timer1_config_t *_timer){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER0 */
        TIMER1_MODULE_DISABLE();
        /* Disable  TIMER0 interrupt*/
        #if TIMER1_INTERRUPT_FEATURE==ENABLE
        TIMER1_InterruptDisable();
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
#if TIMER1_CONFIG==ENABLE
Std_ReturnType Timer1_Write_Value(const timer1_config_t *_timer, uint16 _value){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
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
#if TIMER1_CONFIG==ENABLE
Std_ReturnType Timer1_Read_Value(const timer1_config_t *_timer, uint16 *_value){
    
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_value = 0, h_value = 0;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        l_value = TMR1L;
        h_value = TMR1H;
        *_value = (uint16)((h_value << 8) + l_value);
        ret = E_OK;
    }
    return ret;
}
#endif


static inline void Timer1_Mode_Select(const timer1_config_t *_timer){
    if(TIMER1_TIMER_MODE == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode){
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode){
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
    }
}

static inline void timer1_reg_wr_mode_Select(const timer1_config_t *_timer){
    if(TIMER1_RW_REG_16Bit_MODE == _timer->timer1_reg_wr_mode){
        TIMER1_RW_REG_16BIT_MODE_ENABLE();
    }
    else if(TIMER1_RW_REG_8Bit_MODE == _timer->timer1_reg_wr_mode){
        TIMER1_RW_REG_8BIT_MODE_ENABLE();
    }
}

static inline void TIMER1_OSC_HW_select(const timer1_config_t *_timer){
    if(TIMER1_OSCILLATOR_ENABLE == _timer->timer1_osc_cfg){
        TIMER1_OSC_HW_ENABLE();
    }
    else if(TIMER1_OSCILLATOR_DISABLE == _timer->timer1_osc_cfg){
        TIMER1_OSC_HW_DISABLE();
    }
}

/*
 * Internal Interrupt TIMER1 MCAL Helper function 
 */
void TMR1_ISR(void){
    //clear TIMER0 interrupt flag
    TIMER1_InterruptFlagClear();
    //restore prescaler value
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (uint8)(timer1_preload);
    //Application Callback function gets called every time this ISR executes
    if(TMR1_InterruptHandler){TMR1_InterruptHandler();}
}