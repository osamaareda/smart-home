/* 
 * File:   timer2.h
 * Author: osama reda
 *
 * Created on December 6, 2023, 1:47 AM
 */

#ifndef TIMER2_H
#define	TIMER2_H

/*-----------------------includes-------------------------*/
#include "../GPIO/gpio.h"
#include"mcal_timer2_cfg.h"
#include"../INTERRUPT/mcal_internal_interrupt.h"

/* ----------------- Macro Functions Declarations -----------------*/
/* Enable or Disable Timer2 Module */
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

/* Timer1 Input Clock Pre-scaler */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_) (T2CONbits.T2CKPS = _PRESCALER_)

/* Timer1 Input Clock Post-scaler */
#define TIMER2_POSTSCALER_SELECT(_POSTRSCALER_) (T2CONbits.TOUTPS = _POSTRSCALER_)
/* ----------------- Data Type Declarations -----------------*/
/**
 * Timer2 Pre-Scaler Select 
 */
typedef enum{
    TIMER2_PRESCALER_DIV_BY_1= 0,
    TIMER2_PRESCALER_DIV_BY_2,        
    TIMER2_PRESCALER_DIV_BY_4,
    TIMER2_PRESCALER_DIV_BY_8,
}timer2_prescaler_select_t;

/**
 * Timer2 Post-Scaler Select 
 */
typedef enum{
    TIMER2_POSTSCALER_DIV_BY_1= 0,
    TIMER2_POSTSCALER_DIV_BY_2,        
    TIMER2_POSTSCALER_DIV_BY_3,
    TIMER2_POSTSCALER_DIV_BY_4,
    TIMER2_POSTSCALER_DIV_BY_5,
    TIMER2_POSTSCALER_DIV_BY_6,        
    TIMER2_POSTSCALER_DIV_BY_7,
    TIMER2_POSTSCALER_DIV_BY_8,
    TIMER2_POSTSCALER_DIV_BY_9,
    TIMER2_POSTSCALER_DIV_BY_10,        
    TIMER2_POSTSCALER_DIV_BY_11,
    TIMER2_POSTSCALER_DIV_BY_12,
    TIMER2_POSTSCALER_DIV_BY_13,
    TIMER2_POSTSCALER_DIV_BY_14,        
    TIMER2_POSTSCALER_DIV_BY_15,
    TIMER2_POSTSCALER_DIV_BY_16,
}timer2_POSTSCALER_select_t;

typedef struct{
#if TIMER2_INTERRUPT_FEATURE==ENABLE
    void (* TMR2_InterruptHandler)(void);
    interrupt_priority_t priority;
#endif
    uint8 timer2_preload_value;        /* Preload value configuration */
    timer2_POSTSCALER_select_t timer2_postscaler_value;   /* Postscale value configuration */
    timer2_prescaler_select_t timer2_prescaler_value;   /* Prescale value configuration */
    uint8 timer2_reserved : 2;
}timer2_config_t;


/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Timer2_Init(const timer2_config_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_config_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_config_t *_timer, uint8 _value);
Std_ReturnType Timer2_Read_Value(const timer2_config_t *_timer, uint8 *_value);

#endif	/* TIMER2_H */

