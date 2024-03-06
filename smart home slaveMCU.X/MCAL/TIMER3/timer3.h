/* 
 * File:   timer3.h
 * Author: osama reda
 *
 * Created on December 6, 2023, 4:38 AM
 */

#ifndef TIMER3_H
#define	TIMER3_H

/*-----------------------includes-------------------------*/
#include "../GPIO/gpio.h"
#include"mcal_timer3_cfg.h"
#include"../INTERRUPT/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_COUNTER_MODE            1
#define TIMER3_TIMER_MODE              0
/* Timer3 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE      1
#define TIMER3_SYNC_COUNTER_MODE       0
/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_16Bit_MODE       1
#define TIMER3_RW_REG_8Bit_MODE        0

/* ----------------- Macro Functions Declarations -----------------*/
/* Enable or Disable Timer3 Module */
#define TIMER3_MODULE_ENABLE()              (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()             (T3CONbits.TMR3ON = 0)
/*  Timer3 Clock Source (Timer or Counter) */
#define TIMER3_COUNTER_MODE_ENABLE()        (T3CONbits.TMR3CS = 1)
#define TIMER3_TIMER_MODE_ENABLE()          (T3CONbits.TMR3CS = 0)
/*  Timer1 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 0)
/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()   (T3CONbits.RD16 = 1)
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()    (T3CONbits.RD16 = 0)
/* Timer3 Input Clock Pre-scaler */
#define TIMER3_PRESCALER_SELECT(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_)

/* ----------------- Data Type Declarations -----------------*/
/**
 * Timer0 Pre-Scaler Select 
 */
typedef enum{
    TIMER3_PRESCALER_DIV_BY_1= 0,
    TIMER3_PRESCALER_DIV_BY_2,        
    TIMER3_PRESCALER_DIV_BY_4,
    TIMER3_PRESCALER_DIV_BY_8,
}timer3_prescaler_select_t;

typedef struct{
#if TIMER3_INTERRUPT_FEATURE==ENABLE
    void (* TMR3_InterruptHandler)(void);
    interrupt_priority_t priority;
#endif
    timer3_prescaler_select_t timer3_prescaler_value;   /* Prescale value configuration */
    uint16 timer3_preload_value;        /* Preload value configuration */
    uint8 timer3_mode : 1;              /* Timer Mode / Counter Mode */
    uint8 timer3_counter_mode : 1;      /* Synchronous or ASynchronous Counter */
    uint8 timer3_reg_wr_mode : 1;       /* One 16-bit operation or Two 8-bit operations */
    uint8 timer3_reserved : 5;
}timer3_config_t;


/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Timer3_Init(const timer3_config_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_config_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_config_t *_timer, uint16 _value);
Std_ReturnType Timer3_Read_Value(const timer3_config_t *_timer, uint16 *_value);

#endif	/* TIMER3_H */

