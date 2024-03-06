/* 
 * File:   app.c
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */

#include "app.h"


/*=============================main code===============================*/
volatile uint8_t var_slave;
void MY_I2C_slave_ISR(void){
    uint8  temp_var=SSPBUF;
    if(temp_var==112){
        /*noting*/
    }
    else{
        var_slave=SSPBUF;
        print_num_7seg(var_slave);
    }
}

void main(void)
{

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // Initialize the device
    Initialize();
    I2C_Open();
    I2C_SlaveSetReadIntHandler(MY_I2C_slave_ISR);

    while (1)
    {
        if(var_slave>=30){
            dc_motor_move_right(&motor1);
            dc_motor_stop(&motor2);
            led_on(&led_blue);
            CCP_PWM_Set_Duty(&ccp1,var_slave*2.5);
            CCP_PWM_Start(&ccp1);
        }
         else if(var_slave<30&&var_slave>25){
            dc_motor_stop(&motor1);
            dc_motor_stop(&motor2);
            led_off(&led_blue);
            led_off(&led_red);
            
        }
        else if(var_slave<=25){
            dc_motor_move_right(&motor2);
            dc_motor_stop(&motor1);
            led_on(&led_red);
            
        }
    }
}


void print_num_7seg(uint8 num){
    seven_segment_write(&seg_2,num%10);
    seven_segment_write(&seg_1,num/10);
}
