/* 
 * File:   app.c
 * Author: osama reda
 * Created on march 3, 2024, 4:00 PM
 */

#include "app.h"
#include "ECUAL/buzzer/buzzer.h"

/*=============================main code===============================*/
volatile RealTimeClockDS1307_T RTC1307;
volatile RealTimeClockDS1307_T ALARM_RTC;
volatile uint8 mode_counter=0;
volatile uint8 option_counter=0;
volatile uint8 seconds_counter=0;
volatile uint8 minutes_counter=0;
volatile uint8 hours_counter=0;
volatile uint8 day_counter=1;
volatile uint8 month_counter=1;
volatile uint8 year_counter=1;
uint8 temp_var,adc_value;

void APP_INT0_ISR(void){
    if(option_counter==0){
       RTC1307 = RealTimeClockDS1307_Get_Date_Time();
    }
    option_counter++;
    if(option_counter==6){
       option_counter=0;
       /*send the updated values to the RTC*/
        I2C_Write1ByteRegister(0xD0, 0x00,0);
        convert_int_to_BCD(minutes_counter,&RTC1307._Minutes);
        I2C_Write1ByteRegister(0xD0, 0x01,RTC1307._Minutes);
        convert_int_to_BCD(hours_counter,&RTC1307._Hours);
        I2C_Write1ByteRegister(0xD0, 0x02,RTC1307._Hours);
        convert_int_to_BCD(day_counter,&RTC1307._Day);
        I2C_Write1ByteRegister(0xD0, 0x04,RTC1307._Day);
        convert_int_to_BCD(month_counter,&RTC1307._Month);
        I2C_Write1ByteRegister(0xD0, 0x05,RTC1307._Month);
        convert_int_to_BCD(year_counter,&RTC1307._Year);
        I2C_Write1ByteRegister(0xD0, 0x06,RTC1307._Year);
   }
}

void APP_INT1_ISR(void){
    
    if(option_counter==1){ /*for minutes*/
        minutes_counter++;
        if(minutes_counter>59){
            minutes_counter=0;
        }
    }
    else if(option_counter==2){ /*for hours*/
        hours_counter++;
        if(hours_counter>23){
            hours_counter=0;
        }
    }
    else if(option_counter==3){ /*for day*/
        day_counter++;
        if(day_counter>30){
            day_counter=1;
        }
    }
    else if(option_counter==4){ /*for month*/ 
        month_counter++;
        if(month_counter>12){
            month_counter=1;
        }
    }
    else if(option_counter==5){ /*for year*/
        year_counter++;
         if(year_counter>99){
            year_counter=1;
        }
    }
}

void APP_INT2_ISR(void){
    mode_counter=1;
    option_counter++;
    if(option_counter==4){
        mode_counter=0;
        option_counter=0;
        ALARM_RTC._Minutes=minutes_counter;
        ALARM_RTC._Hours=hours_counter;
        ALARM_RTC._Day=day_counter;
    }
}

void MY_ADC_ISR(void){
    ADC_GetConversionResult(&adc,&adc_value);
    EUSART_ASYNC_WriteByteNonBlocking(adc_value);
}

void main(void)
{
    //Initialize the device
    _Initialize();
    
    while (1)
    {
       
        temp_var=I2C_Read1ByteRegister(0x9A,0x00);
        I2C_Write1ByteRegister(0x70,0x00,temp_var);
        __delay_ms(100);
         ADC_StartConversion_Interrupt(&adc,ADC_CHANNEL_AN0);
            if(option_counter==0){ /*for seconds*/
                /*getting TIME value and display it on the LCD*/
                RTC1307 = RealTimeClockDS1307_Get_Date_Time();
                lcd_send_command(&lcd,_LCD_CLEAR);
                lcd_send_string_pos(&lcd,1,1,"TIME:");
                convert_BCD_to_int(RTC1307._Hours,&hours_counter);
                lcd_send_number_pos(&lcd,1,7,hours_counter);
                lcd_send_char_data_pos(&lcd,1,9,':');
                convert_BCD_to_int(RTC1307._Minutes,&minutes_counter);
                lcd_send_number_pos(&lcd,1,10,minutes_counter);
                lcd_send_char_data_pos(&lcd,1,12,':');
                convert_BCD_to_int(RTC1307._Seconds,&seconds_counter);
                lcd_send_number_pos(&lcd,1,13,seconds_counter);

                /*getting DATE value and display it on the LCD*/
                lcd_send_string_pos(&lcd,2,1,"DATE:");
                convert_BCD_to_int(RTC1307._Day,&day_counter);
                lcd_send_number_pos(&lcd,2,7,day_counter);
                lcd_send_char_data_pos(&lcd,2,9,'/');
                convert_BCD_to_int(RTC1307._Month,&month_counter);
                lcd_send_number_pos(&lcd,2,10,RTC1307._Month);
                lcd_send_char_data_pos(&lcd,2,12,'/');
                convert_BCD_to_int(RTC1307._Year,&year_counter);
                lcd_send_number_pos(&lcd,2,13,year_counter);
                __delay_ms(500);
                if(minutes_counter==ALARM_RTC._Minutes && hours_counter==ALARM_RTC._Hours){
                    buzzer_on(&buzzer);
                    __delay_ms(500);
                    buzzer_off(&buzzer);
                    __delay_ms(500);
                }
                
            }
            if(mode_counter==0){
                if(option_counter==1){
                    /*display minutes on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"CLOCK MODE");
                    lcd_send_string_pos(&lcd,2,1,"minutes:");
                    lcd_send_number_pos(&lcd,2,10,minutes_counter);
                    __delay_ms(500);
                    
                }
                else if(option_counter==2){
                    /*display hours on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"CLOCK MODE");
                    lcd_send_string_pos(&lcd,2,1,"hours:");
                    lcd_send_number_pos(&lcd,2,8,hours_counter);
                    __delay_ms(500);
                }
                else if(option_counter==3){
                    /*display day on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"CLOCK MODE");
                    lcd_send_string_pos(&lcd,2,1,"day:");
                    lcd_send_number_pos(&lcd,2,6,day_counter);
                    __delay_ms(500);
                }
                else if(option_counter==4){
                    /*display month on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"CLOCK MODE");
                    lcd_send_string_pos(&lcd,2,1,"month:");
                    lcd_send_number_pos(&lcd,2,8,month_counter);
                    __delay_ms(500);
                }
                else if(option_counter==5){
                    /*display year on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"CLOCK MODE");
                    lcd_send_string_pos(&lcd,2,1,"year:");
                    lcd_send_number_pos(&lcd,2,7,year_counter);
                    __delay_ms(500);
                }
            }
            else if(mode_counter==1){
                if(option_counter==1){
                    /*display minutes on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"ALLARM MODE");
                    lcd_send_string_pos(&lcd,2,1,"minutes:");
                    lcd_send_number_pos(&lcd,2,10,minutes_counter);
                    __delay_ms(500);
                }
                else if(option_counter==2){
                    /*display hours on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"ALLARM MODE");
                    lcd_send_string_pos(&lcd,2,1,"hours:");
                    lcd_send_number_pos(&lcd,2,8,hours_counter);
                    __delay_ms(500);
                }
                else if(option_counter==3){
                    /*display day on the LCD while updating it*/
                    lcd_send_command(&lcd,_LCD_CLEAR);
                    lcd_send_string_pos(&lcd,1,1,"ALLARM MODE");
                    lcd_send_string_pos(&lcd,2,1,"day:");
                    lcd_send_number_pos(&lcd,2,6,day_counter);
                    __delay_ms(500);
                }
            }
    }
}