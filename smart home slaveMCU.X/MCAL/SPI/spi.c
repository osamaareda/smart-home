/* 
 * File:   spi.c
 * Author: osama reda
 *
 * Created on January 23, 2024, 7:41 PM
 */
#include "spi.h"
#if SPI_INTERRUPT_FEATURE==ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif

/* helper function to initialize SPI interrupt */
static void SPI_Interrupt_Init(const spi_config_t *_spi);
static void SPI_Master_Mode_GPIO_PIN_Configurations(void);
static void SPI_Slave_Mode_GPIO_PIN_Configurations(const spi_config_t *_spi);
    
Std_ReturnType SPI_Init(const spi_config_t *_spi){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _spi){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* SPI Mode Select */
        SSPCON1bits.SSPM=_spi->spi_mode;
        /* GPIO PIN Configurations */
        if(_spi->spi_mode==SPI_MASTER_FOSC_DIV4 || _spi->spi_mode==SPI_MASTER_FOSC_DIV16 
            || _spi->spi_mode==SPI_MASTER_FOSC_DIV64 || _spi->spi_mode==SPI_MASTER_FOSC_TMR2){
            SPI_Master_Mode_GPIO_PIN_Configurations();
        }
        else if(_spi->spi_mode==SPI_SLAVE_SS_ENABLE || _spi->spi_mode==SPI_SLAVE_SS_DISABLE ){
            SPI_Slave_Mode_GPIO_PIN_Configurations(_spi);
        }
        /* Clock Polarity Select */
        SSPCON1bits.CKP=_spi->clock_polarity;
        /* SPI Clock phase Select */
        SSPSTATbits.CKE=_spi->clock_phase;
        /* SPI Sample Select */
        SSPSTATbits.SMP=_spi->sample;
        /* SPI Interrupt Configurations*/
        SPI_Interrupt_Init(_spi);
        /* Enable SPI Module */
        SPI_ENABLE_MODULE();
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType SPI_DeInit(const spi_config_t *_spi){
     Std_ReturnType ret = E_NOT_OK;
    if(NULL == _spi){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* Disable Interrupt */ 
        #if SPI_INTERRUPT_FEATURE==ENABLE
        SPI_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType SPI_Send_Byte(const spi_config_t *_spi, const uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _spi){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF=_data;
        while(!(PIR1bits.SSPIF));
        PIR1bits.SSPIF=0;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_Read_Byte(const spi_config_t *_spi, uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _spi || NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        while(SSPSTATbits.BF==0);
        *_data=SSPBUF;
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType SPI_Send_Byte_NonBlocking(const spi_config_t *_spi, const uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _spi){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF=_data;
        if(PIR1bits.SSPIF==1){
            PIR1bits.SSPIF=0;
        }
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType SPI_Read_Byte_NonBlocking(const spi_config_t *_spi, uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _spi || NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        if(SSPSTATbits.BF==1){
           *_data=SSPBUF;
        }
        ret = E_OK;
    }
    return ret;
}



static void SPI_Interrupt_Init(const spi_config_t *_spi){
    
    #if SPI_INTERRUPT_FEATURE==ENABLE
    SPI_InterruptFlagClear();
    #if INTERRUPT_PRIORITY_LEVELS==ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if(HIGH_PRIORITY == _spi->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
         SPI_HighPrioritySet();
    }
    else if(LOW_PRIORITY == _spi->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        SPI_LowPrioritySet();
    }
    #elif INTERRUPT_PRIORITY_LEVELS==DISABLE
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    #endif
    SPI_InterruptEnable();
    SPI_InterruptHandler=_spi->SPI_InterruptHandler;
    #endif      
}

   
static void SPI_Master_Mode_GPIO_PIN_Configurations(void){
    
    pin_config_t SCK_pin={.port=PORTC_INDEX,.pin=PIN3};
    pin_config_t SDI_pin={.port=PORTC_INDEX,.pin=PIN4};
    pin_config_t SDO_pin={.port=PORTC_INDEX,.pin=PIN5};
    
    gpio_pin_direction_init(&SCK_pin,OUTPUT);
    gpio_pin_direction_init(&SDI_pin,INPUT);
    gpio_pin_direction_init(&SDO_pin,OUTPUT);
}
static void SPI_Slave_Mode_GPIO_PIN_Configurations(const spi_config_t *_spi){
    
    pin_config_t SCK_pin={.port=PORTC_INDEX,.pin=PIN3};
    pin_config_t SDI_pin={.port=PORTC_INDEX,.pin=PIN4};
    pin_config_t SDO_pin={.port=PORTC_INDEX,.pin=PIN5};
    pin_config_t SS_pin={.port=PORTA_INDEX,.pin=PIN5};
     
    gpio_pin_direction_init(&SCK_pin,INPUT);
    gpio_pin_direction_init(&SDI_pin,INPUT);
    gpio_pin_direction_init(&SDO_pin,OUTPUT);
    if(SPI_SLAVE_SS_ENABLE == _spi->spi_mode){
    gpio_pin_direction_init(&SS_pin,INPUT);
    }
}

/*
 * Internal Interrupt SPI MCAL Helper function 
 */
void SPI_ISR(void){
    //disable the interrupt
    SPI_InterruptFlagClear();
    //Application Callback function gets called every time this ISR executes
    if(SPI_InterruptHandler){SPI_InterruptHandler();}
}