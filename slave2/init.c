/* 
 * File:   init.c
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */
#include "init.h"

/*============================uart configuration===========================*/
usart_config_t uart={
    .baudrate=9600,
    .baudrate_gen_gonfig=BAUDRATE_ASYN_8BIT_lOW_SPEED,
    .usart_rx_cfg.usart_rx_enable=EUSART_ASYNCHRONOUS_RX_ENABLE,
    .usart_rx_cfg.usart_rx_9bit_enable=EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable=EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
    .EUSART_RxDefaultInterruptHandler=NULL
};
/*============================led configuration===========================*/
led_config_t led_yellow={.led_pin.port=PORTD_INDEX,.led_pin.pin=PIN0};
led_config_t led_1={.led_pin.port=PORTD_INDEX,.led_pin.pin=PIN2};
led_config_t led_2={.led_pin.port=PORTD_INDEX,.led_pin.pin=PIN3};
led_config_t led_3={.led_pin.port=PORTD_INDEX,.led_pin.pin=PIN4};
led_config_t led_4={.led_pin.port=PORTD_INDEX,.led_pin.pin=PIN5};

/*============================relay configuration===========================*/
relay_config_t relay={.relay_pin.port=PORTD_INDEX,.relay_pin.pin=PIN1};

/*============================interrupt configuration===========================*/
interrupt_INTx_t MY_INT0={
    .EXT_InterruptHandler=APP_INT0_ISR,
    .INTx_pin.port=PORTB_INDEX,
    .INTx_pin.pin=PIN0,
    .edge=RISING_EDGE,
    .source=_INT0};

interrupt_INTx_t MY_INT1={
    .EXT_InterruptHandler=APP_INT1_ISR,
    .INTx_pin.port=PORTB_INDEX,
    .INTx_pin.pin=PIN1,
    .edge=RISING_EDGE,
    .source=_INT1};

interrupt_INTx_t MY_INT2={
    .EXT_InterruptHandler=APP_INT2_ISR,
    .INTx_pin.port=PORTB_INDEX,
    .INTx_pin.pin=PIN2,
    .edge=RISING_EDGE,
    .source=_INT2};

interrupt_RBx_t MY_RB0={
    .EXT_InterruptHandler_HIGH=APP_RB0_ISR,
    .EXT_InterruptHandler_LOW=NULL,
    .RBx_pin.port=PORTB_INDEX,
    .RBx_pin.pin=PIN4,
};

interrupt_RBx_t MY_RB1={
    .EXT_InterruptHandler_HIGH=APP_RB1_ISR,
    .EXT_InterruptHandler_LOW=NULL,
    .RBx_pin.port=PORTB_INDEX,
    .RBx_pin.pin=PIN5,
};

interrupt_RBx_t MY_RB2={
    .EXT_InterruptHandler_HIGH=APP_RB2_ISR,
    .EXT_InterruptHandler_LOW=NULL,
    .RBx_pin.port=PORTB_INDEX,
    .RBx_pin.pin=PIN6,
};


/*============================timer0 configuration==========================*/
timer0_config_t timer0={
    .TMR0_InterruptHandler=MY_TMR0_ISR,
    .prescaler_enable=TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value=TIMER0_PRESCALER_DIV_BY_32,
    .timer0_mode=TIMER0_TIMER_MODE,
    .timer0_register_size=TIMER0_16BIT_REGISTER_MODE,
    .timer0_preload_value=3036
};

/*============================motor configuration===========================*/
//door motor
dc_motor_config_t door_motor={.dc_motor_pin0.port=PORTD_INDEX,.dc_motor_pin0.pin=PIN6,
                              .dc_motor_pin1.port=PORTD_INDEX,.dc_motor_pin1.pin=PIN7};

/*============================lcd configuration===========================*/
lcd_config_t lcd={.lcd_rs.port=PORTC_INDEX,.lcd_rs.pin=PIN4,
                  .lcd_en.port=PORTC_INDEX,.lcd_en.pin=PIN5,
                  .lcd_pins[0].port=PORTC_INDEX,.lcd_pins[0].pin=PIN0,
                  .lcd_pins[1].port=PORTC_INDEX,.lcd_pins[1].pin=PIN1,
                  .lcd_pins[2].port=PORTC_INDEX,.lcd_pins[2].pin=PIN2,
                  .lcd_pins[3].port=PORTC_INDEX,.lcd_pins[3].pin=PIN3};

/*===========================keypad configuration=========================*/
keypad_config_t keypad={.keypad_rows_pins[0].port=PORTA_INDEX,.keypad_rows_pins[0].pin=PIN1,
                        .keypad_rows_pins[1].port=PORTA_INDEX,.keypad_rows_pins[1].pin=PIN2,
                        .keypad_rows_pins[2].port=PORTA_INDEX,.keypad_rows_pins[2].pin=PIN3,
                        .keypad_rows_pins[3].port=PORTA_INDEX,.keypad_rows_pins[3].pin=PIN5,
                        .keypad_columns_pins[0].port=PORTB_INDEX,.keypad_columns_pins[0].pin=PIN0,
                        .keypad_columns_pins[1].port=PORTB_INDEX,.keypad_columns_pins[1].pin=PIN1,
                        .keypad_columns_pins[2].port=PORTB_INDEX,.keypad_columns_pins[2].pin=PIN2,
                        .keypad_columns_pins[3].port=PORTB_INDEX,.keypad_columns_pins[3].pin=PIN4
                       };

void Initialize(void){
    EUSART_ASYNC_Init(&uart);
    led_init(&led_yellow);
    led_init(&led_1);
    led_init(&led_2);
    led_init(&led_3);
    led_init(&led_4);
    relay_init(&relay);
    interrupt_INTx_init(&MY_INT0);
    interrupt_INTx_init(&MY_INT1);
    interrupt_INTx_init(&MY_INT2);
    interrupt_RBx_init(&MY_RB0);
    interrupt_RBx_init(&MY_RB1);
    interrupt_RBx_init(&MY_RB2);
    Timer0_Init(&timer0);
    dc_motor_init(&door_motor);
    lcd_init(&lcd);
    keypad_init(&keypad);
}



