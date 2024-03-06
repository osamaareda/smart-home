/* 
 * File:   usart.c
 * Author: osama reda
 *
 * Created on December 19, 2023, 3:42 AM
 */

#include "usart.h"

#if EUSART_TX_INTERRUPT_FEATURE==ENABLE
    static void (*EUSART_TxInterruptHandler)(void) = NULL;
#endif
#if EUSART_RX_INTERRUPT_FEATURE==ENABLE
    static void (*EUSART_RxInterruptHandler)(void) = NULL;
    static void (*EUSART_FramingErrorHandler)(void) = NULL;
    static void (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif    
    
/* helper function to initialize EUSART interrupt */
static void EUSART_Baud_Rate_Calculation(const usart_config_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_config_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_config_t *_eusart);

Std_ReturnType EUSART_ASYNC_Init(const usart_config_t *_eusart){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE; /* Disable EUSART Module */
        TRISCbits.RC7 = 1;                      /* RX : Input Configuration as needed */
        TRISCbits.RC6 = 1;                      /* TX : Input Configuration as needed */
        EUSART_Baud_Rate_Calculation(_eusart);
        EUSART_ASYNC_TX_Init(_eusart);
        EUSART_ASYNC_RX_Init(_eusart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;  /* Enable EUSART Module */
        ret = E_OK;
    }
    
    return ret;
}
Std_ReturnType EUSART_ASYNC_DeInit(const usart_config_t *_eusart){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN=EUSART_MODULE_DISABLE; /* Disable EUSART Module */
        ret = E_OK;
    }
    
    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 _data){
    
    Std_ReturnType ret = E_NOT_OK;
    while(!TXSTAbits.TRMT);
    #if EUSART_TX_INTERRUPT_FEATURE_ENABLE==ENABLE
    EUSART_TX_InterruptEnable();
    #endif
    TXREG=_data;
    ret = E_OK;
    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len){
 
    Std_ReturnType ret = E_NOT_OK;
    uint16 char_counter=0;
    for(char_counter=0;char_counter<str_len;char_counter++){
        ret=EUSART_ASYNC_WriteByteBlocking(_data[char_counter]);
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data){
    
    Std_ReturnType ret = E_NOT_OK;
    if(1==TXSTAbits.TRMT){
        #if EUSART_TX_INTERRUPT_FEATURE==ENABLE
        EUSART_TX_InterruptEnable();
        #endif
        TXREG=_data;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len){
    
    Std_ReturnType ret = E_NOT_OK;
    uint16 char_counter=0;
    if(1==TXSTAbits.TRMT){
        for(char_counter=0;char_counter<str_len;char_counter++){
        ret=EUSART_ASYNC_WriteByteBlocking(_data[char_counter]);
        }
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data){
    
    Std_ReturnType ret = E_NOT_OK;
    while(!PIR1bits.RCIF);
    *_data=RCREG;
    ret = E_OK;
    return ret;
}
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(1==PIR1bits.RCIF){
        *_data=RCREG;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN=0; /* Disables receiver */
    RCSTAbits.CREN=1; /* Enables receiver */
    return ret;
}

static void EUSART_Baud_Rate_Calculation(const usart_config_t *_eusart){
   
    float Baud_Rate_Temp = 0;
    switch(_eusart->baudrate_gen_gonfig){
        case BAUDRATE_ASYN_8BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        default : ;
    }
    SPBRG = (uint8)((uint32)Baud_Rate_Temp);
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp) >> 8);
}
    

static void EUSART_ASYNC_TX_Init(const usart_config_t *_eusart){
    
    if(EUSART_ASYNCHRONOUS_TX_ENABLE==_eusart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN=EUSART_ASYNCHRONOUS_TX_ENABLE;
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE==_eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            /* Configure the interrupt  */        
            #if EUSART_TX_INTERRUPT_FEATURE==ENABLE
            EUSART_TX_InterruptDisable();
            #if INTERRUPT_PRIORITY_LEVELS==ENABLE 
            INTERRUPT_PriorityLevelsEnable();
            if(HIGH_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_TX_HighPrioritySet();
            }
            else if(LOW_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_TX_LowPrioritySet();
            }
            #elif INTERRUPT_PRIORITY_LEVELS==DISABLE
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif
            EUSART_TX_InterruptEnable();
            EUSART_TxInterruptHandler=_eusart->EUSART_TxDefaultInterruptHandler;
            #endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE==_eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE=EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE==_eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9=EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE==_eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9=EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
        }
    }

}
static void EUSART_ASYNC_RX_Init(const usart_config_t *_eusart){
    
    if(EUSART_ASYNCHRONOUS_RX_ENABLE==_eusart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN=EUSART_ASYNCHRONOUS_RX_ENABLE;
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE==_eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            /* Configure the interrupt  */        
            #if EUSART_RX_INTERRUPT_FEATURE_ENABLE==ENABLE
            EUSART_RX_InterruptDisable();
            #if INTERRUPT_PRIORITY_LEVELS==ENABLE 
            INTERRUPT_PriorityLevelsEnable();
            if(HIGH_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_RX_HighPrioritySet();
            }
            else if(LOW_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_RX_LowPrioritySet();
            }
            #elif INTERRUPT_PRIORITY_LEVELS==DISABLE
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif
            EUSART_RX_InterruptEnable();
            EUSART_RxInterruptHandler=_eusart->EUSART_RxDefaultInterruptHandler;
            EUSART_FramingErrorHandler=_eusart->EUSART_FramingErrorHandler;
            EUSART_OverrunErrorHandler=_eusart->EUSART_OverrunErrorHandler;
            #endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE==_eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE=EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE==_eusart->usart_rx_cfg.usart_rx_9bit_enable){
            TXSTAbits.TX9=EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE==_eusart->usart_rx_cfg.usart_rx_9bit_enable){
            TXSTAbits.TX9=EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
        }
    }
}

/*
 * Internal Interrupt EUSART_TX MCAL Helper function 
 */
void EUSART_TX_ISR(void){
    //disable the interrupt
    EUSART_TX_InterruptDisable();
    //Application Callback function gets called every time this ISR executes
    if(EUSART_TxInterruptHandler){EUSART_TxInterruptHandler();}
}

/*
 * Internal Interrupt EUSART_RX MCAL Helper function 
 */
void EUSART_RX_ISR(void){
    //Application Callback function gets called every time this ISR executes
    if(EUSART_RxInterruptHandler){EUSART_RxInterruptHandler();}
    if(EUSART_FramingErrorHandler){EUSART_FramingErrorHandler();}
    if(EUSART_OverrunErrorHandler){EUSART_OverrunErrorHandler();}
}