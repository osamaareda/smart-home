/* 
 * File:   init.c
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */

#include "init.h"
/*============================lcd configuration===========================*/
lcd_config_t lcd={.lcd_rs.port=PORTD_INDEX,.lcd_rs.pin=PIN4,
                  .lcd_en.port=PORTD_INDEX,.lcd_en.pin=PIN5,
                  .lcd_pins[0].port=PORTD_INDEX,.lcd_pins[0].pin=PIN0,
                  .lcd_pins[1].port=PORTD_INDEX,.lcd_pins[1].pin=PIN1,
                  .lcd_pins[2].port=PORTD_INDEX,.lcd_pins[2].pin=PIN2,
                  .lcd_pins[3].port=PORTD_INDEX,.lcd_pins[3].pin=PIN3};

/*============================buzzer configuration===========================*/
buzzer_config_t buzzer={.buzzer_pin.port=PORTD_INDEX,.buzzer_pin.pin=PIN6};

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

/*============================adc configuration===========================*/
adc_config_t adc={
    .ADC_InterruptHandler=MY_ADC_ISR,
    .acquisition_time=ADC_12_TAD,
    .adc_channel=ADC_CHANNEL_AN0,
    .result_format=ADC_RESULT_RIGHT,
    .voltage_reference=ADC_VOLTAGE_REFERENCE_DISABLED,
    .conversion_clock=ADC_CONVERSION_CLOCK_FOSC_DIV_16
};
/*============================uart configuration===========================*/
usart_config_t uart={
    .baudrate=9600,
    .baudrate_gen_gonfig=BAUDRATE_ASYN_8BIT_lOW_SPEED,
    .usart_tx_cfg.usart_tx_enable=EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable=EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable=EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
};

void _Initialize(void){
    
    I2C_Initialize();
    lcd_init(&lcd);
    interrupt_INTx_init(&MY_INT0);
    interrupt_INTx_init(&MY_INT1);
    interrupt_INTx_init(&MY_INT2);
    buzzer_init(&buzzer);
    ADC_Init(&adc);
    EUSART_ASYNC_Init(&uart);
}


