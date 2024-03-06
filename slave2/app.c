/* 
 * File:   app.c
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */
 
#include"app.h"

Std_ReturnType ret=E_NOT_OK;
volatile uint8 uart_value;
volatile uint8 led_var=0;
volatile uint8 timer0_var=0;
volatile uint8 keypad_var1=0,keypad_var2=0,keypad_var3=0,keypad_var4=0;
volatile uint8 pass_value=0;
volatile uint8 digit1=0,digit2=0,digit3=0;
uint8 keypad_var5=0;
/*=============================main code===============================*/


void APP_INT0_ISR(void){
    keypad_read(&keypad,&keypad_var1);
    if(keypad_var1=='#'){
            if(pass_value==0 || pass_value==0xFF){
                lcd_send_command(&lcd,_LCD_CLEAR);
                lcd_send_string_pos(&lcd,1,1,"create pass:");
            }
            else if(pass_value==1){
                lcd_send_command(&lcd,_LCD_CLEAR);
                lcd_send_string_pos(&lcd,1,1,"enter your pass:");
            }
    }
    else{
        if(pass_value==0 || pass_value==0xFF){
            EEPROM_WriteByte(0x0010,keypad_var1);
            lcd_send_char_data_pos(&lcd,1,13,keypad_var1);
            __delay_ms(250);
            lcd_send_char_data_pos(&lcd,1,13,'*');
        }
        else if(pass_value==1){
            uint8 temp_keypad_var1;
            keypad_read(&keypad,&keypad_var1);
            lcd_send_char_data_pos(&lcd,1,17,keypad_var1);
            __delay_ms(250);
            lcd_send_char_data_pos(&lcd,1,17,'*');
            EEPROM_ReadByte(0x0010,&temp_keypad_var1);
            if(temp_keypad_var1==keypad_var1){
            digit1=1;
            }
        }
    }
      
}

void APP_INT1_ISR(void){
    if(pass_value==0 || pass_value==0xFF){
        keypad_read(&keypad,&keypad_var2);
        EEPROM_WriteByte(0x0011,keypad_var2);
        lcd_send_char_data_pos(&lcd,1,14,keypad_var2);
        __delay_ms(250);
        lcd_send_char_data_pos(&lcd,1,14,'*');
    }
    else if(pass_value==1){
        uint8 temp_keypad_var2;
        keypad_read(&keypad,&keypad_var2);
        lcd_send_char_data_pos(&lcd,1,18,keypad_var2);
        __delay_ms(250);
        lcd_send_char_data_pos(&lcd,1,18,'*');
        EEPROM_ReadByte(0x0011,&temp_keypad_var2);
        if(temp_keypad_var2==keypad_var2){
        digit2=1;
        }
    }
}

void APP_INT2_ISR(void){
    keypad_read(&keypad,&keypad_var3);
        if(pass_value==0 || pass_value==0xFF){
            EEPROM_WriteByte(0x0012,keypad_var3);
            lcd_send_char_data_pos(&lcd,1,15,keypad_var3);
            __delay_ms(250);
            lcd_send_char_data_pos(&lcd,1,15,'*');
        }
        else if(pass_value==1){
            uint8 temp_keypad_var3;
            keypad_read(&keypad,&keypad_var3);
            lcd_send_char_data_pos(&lcd,1,19,keypad_var3);
            __delay_ms(250);
            lcd_send_char_data_pos(&lcd,1,19,'*');
            EEPROM_ReadByte(0x0012,&temp_keypad_var3);
            if(temp_keypad_var3==keypad_var3){
            digit3=1;
            }
            if(digit1==1 && digit2==1 && digit3==1){
                lcd_send_command(&lcd,_LCD_CLEAR);
                lcd_send_string_pos(&lcd,1,1,"correct pass:");
                lcd_send_string_pos(&lcd,2,1,"open the gate");
                dc_motor_move_right(&door_motor);
                __delay_ms(1500);
                dc_motor_stop(&door_motor);
                lcd_send_command(&lcd,_LCD_CLEAR);
                print_welcome();
            }
            else{
                lcd_send_command(&lcd,_LCD_CLEAR);
                lcd_send_string_pos(&lcd,1,1,"wrong pass:");
                lcd_send_string_pos(&lcd,2,1,"please try again");
                __delay_ms(1000);
                lcd_send_command(&lcd,_LCD_CLEAR);
                lcd_send_string_pos(&lcd,1,1,"enter your pass:");
            }
        }
    }
      
void APP_RB0_ISR(void){
    if(pass_value==0){
        pass_value=1;
        EEPROM_WriteByte(0x0013,pass_value);
        lcd_send_command(&lcd,_LCD_CLEAR);
        lcd_send_string_pos(&lcd,2,1,"pass saved");
        __delay_ms(1000);
        lcd_send_command(&lcd,_LCD_CLEAR);
        print_welcome();
    }
    else if(pass_value==1){
        lcd_send_command(&lcd,_LCD_CLEAR);
        lcd_send_string_pos(&lcd,2,1,"close the gate");
        dc_motor_move_left(&door_motor);
        __delay_ms(1500);
        dc_motor_stop(&door_motor);
        lcd_send_command(&lcd,_LCD_CLEAR);
        print_welcome();
    }
    
    
}

void APP_RB1_ISR(void){
    pass_value=0;
    EEPROM_WriteByte(0x0013,pass_value);
}

void APP_RB2_ISR(void){
    led_on(&led_yellow);
    Timer0_Write_Value(&timer0,0);
    timer0_var=10;
}

void MY_TMR0_ISR(void){
    timer0_var--;
    _7seg_bcd_write(timer0_var);
    if(timer0_var==0){
        led_off(&led_yellow);
    } 
}


int main() {
    
    
    Initialize();
    print_welcome();
    EEPROM_ReadByte(0x0013,&pass_value);
while(1)
{
    
    keypad_read(&keypad,&keypad_var5);
    EUSART_ASYNC_ReadByteBlocking(&uart_value);
    if(uart_value<50){
        relay_off(&relay);
    }
    else if(uart_value>50){
        relay_on(&relay);
    }

}
    return (EXIT_SUCCESS);
}

void _7seg_bcd_write(uint8 num){
    switch(num){
        case 0:
            led_off(&led_4);led_off(&led_3);led_off(&led_2);led_off(&led_1);//0000
            break;
        case 1:
            led_off(&led_4);led_off(&led_3);led_off(&led_2);led_on(&led_1);//0001
            break;
        case 2:
            led_off(&led_4);led_off(&led_3);led_on(&led_2);led_off(&led_1);//0010
            break;
        case 3:
            led_off(&led_4);led_off(&led_3);led_on(&led_2);led_on(&led_1);//0011
            break;
        case 4:
            led_off(&led_4);led_on(&led_3);led_off(&led_2);led_off(&led_1);//0100
            break;   
        case 5:
            led_off(&led_4);led_on(&led_3);led_off(&led_2);led_on(&led_1);//0101
            break;   
        case 6:
            led_off(&led_4);led_on(&led_3);led_on(&led_2);led_off(&led_1);//0110
            break;
        case 7:
            led_off(&led_4);led_on(&led_3);led_on(&led_2);led_on(&led_1);//0111
            break;
        case 8:
            led_on(&led_4);led_off(&led_3);led_off(&led_2);led_off(&led_1);//1000
            break;
        case 9:
            led_on(&led_4);led_off(&led_3);led_off(&led_2);led_on(&led_1);//1001
            break;
    }
}

/*========================custom characters=========================*/
uint8 customChar1[] = {0x01,0x03,0x07,0x0E,0x1E,0x1F,0x1F,0x1F};
uint8 customChar2[] = {0x1F,0x1F,0x1F,0x0E,0x0E,0x1F,0x1F,0x1F};
uint8 customChar3[] = {0x10,0x18,0x1C,0x06,0x07,0x1F,0x1F,0x1F};
uint8 customChar4[] = {0x13,0x18,0x1C,0x1E,0x0F,0x07,0x03,0x01};
uint8 customChar5[] = {0x1F,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};
uint8 customChar6[] = {0x1B,0x03,0x07,0x0F,0x1E,0x1C,0x18,0x10};
uint8 customChar7[] = {0x01,0x03,0x07,0x0E,0x1C,0x1F,0x1F,0x1F};
uint8 customChar8[] = {0x1F,0x1F,0x1F,0x0E,0x04,0x1F,0x1F,0x1F};
uint8 customChar9[] = {0x10,0x18,0x1C,0x06,0x03,0x1F,0x1F,0x1F};
uint8 customChar10[] = {0x1F,0x1F,0x1E,0x1C,0x0D,0x07,0x03,0x01};
uint8 customChar11[] = {0x1F,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F};
uint8 customChar12[] = {0x1F,0x1F,0x0F,0x07,0x16,0x1C,0x18,0x10};
/*=========================to print welcome==========================*/
void print_welcome(void){
    lcd_send_string_pos(&lcd,1,7,"WELCOM");
    lcd_send_custom_char(&lcd,2,9,customChar1,0);
    lcd_send_custom_char(&lcd,2,10,customChar2,1);
    lcd_send_custom_char(&lcd,2,11,customChar3,2);
    lcd_send_custom_char(&lcd,3,9,customChar4,3);
    lcd_send_custom_char(&lcd,3,10,customChar5,4);
    lcd_send_custom_char(&lcd,3,11,customChar6,5);
}
/*=========================to print smile face=========================*/
void smile_face(void){
    lcd_send_custom_char(&lcd,2,9,customChar1,0);
    lcd_send_custom_char(&lcd,2,10,customChar2,1);
    lcd_send_custom_char(&lcd,2,11,customChar3,2);
    lcd_send_custom_char(&lcd,3,9,customChar4,3);
    lcd_send_custom_char(&lcd,3,10,customChar5,4);
    lcd_send_custom_char(&lcd,3,11,customChar6,5);
}
