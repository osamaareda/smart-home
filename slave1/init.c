/* 
 * File:   init.c
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */

#include "init.h"
/*============================led configuration===========================*/
led_config_t led_red={.led_pin.port=PORTD_INDEX,.led_pin.pin=PIN4};
led_config_t led_blue={.led_pin.port=PORTD_INDEX,.led_pin.pin=PIN5};

/*============================motor configuration===========================*/
//motor1
dc_motor_config_t motor1={.dc_motor_pin0.port=PORTD_INDEX,.dc_motor_pin0.pin=PIN0,
                          .dc_motor_pin1.port=PORTD_INDEX,.dc_motor_pin1.pin=PIN1};
//motor2
dc_motor_config_t motor2={.dc_motor_pin0.port=PORTD_INDEX,.dc_motor_pin0.pin=PIN2,
                          .dc_motor_pin1.port=PORTD_INDEX,.dc_motor_pin1.pin=PIN3};

/*====================7 segments configuration===========================*/
seven_segment_config_t seg_1={.seven_segment_pins[0].port=PORTB_INDEX,.seven_segment_pins[0].pin=PIN0,
                              .seven_segment_pins[1].port=PORTB_INDEX,.seven_segment_pins[1].pin=PIN1,
                              .seven_segment_pins[2].port=PORTB_INDEX,.seven_segment_pins[2].pin=PIN2,
                              .seven_segment_pins[3].port=PORTB_INDEX,.seven_segment_pins[3].pin=PIN3};  

seven_segment_config_t seg_2={.seven_segment_pins[0].port=PORTB_INDEX,.seven_segment_pins[0].pin=PIN4,
                              .seven_segment_pins[1].port=PORTB_INDEX,.seven_segment_pins[1].pin=PIN5,
                              .seven_segment_pins[2].port=PORTB_INDEX,.seven_segment_pins[2].pin=PIN6,
                              .seven_segment_pins[3].port=PORTB_INDEX,.seven_segment_pins[3].pin=PIN7};   
/*====================CCP configuration===========================*/
ccp_t ccp1={.ccp_inst = CCP1_INST,
            .CCP1_InterruptHandler = NULL,
            .ccp_mode = CCP_PWM_MODE_SELECTED,
            .PWM_Frequency = 10000,
            .ccp_pin.port = PORTC_INDEX,
            .ccp_pin.pin = PIN2,
            .ccp_pin.direction = OUTPUT,
            .timer2_prescaler_value = CCP_TIMER2_PRESCALER_DIV_BY_1,
            .timer2_postscaler_value = CCP_TIMER2_POSTSCALER_DIV_BY_1};
/*====================timer2 configuration===========================*/
timer2_config_t timer2={.TMR2_InterruptHandler = NULL,
                        .timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_1,
                        .timer2_postscaler_value = TIMER2_POSTSCALER_DIV_BY_1,
                        .timer2_preload_value = 0};

void Initialize(void)
{
    INTERRUPT_Initialize();
    I2C_Initialize();
    PIN_MANAGER_Initialize();
    led_init(&led_red);
    led_init(&led_blue);
    dc_motor_init(&motor1);
    dc_motor_init(&motor2);
    seven_segment_init(&seg_1);
    seven_segment_init(&seg_2);
    CCP_Init(&ccp1);
    Timer2_Init(&timer2);
}



