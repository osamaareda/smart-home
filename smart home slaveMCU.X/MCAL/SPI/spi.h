/* 
 * File:   spi.h
 * Author: osama reda
 *
 * Created on January 23, 2024, 7:41 PM
 */

#ifndef SPI_H
#define	SPI_H

/* ----------------- Includes -----------------*/
#include "../GPIO/gpio.h"
#include "mcal_spi_cfg.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Master Synchronous Serial Port Mode Select */
#define SPI_MASTER_FOSC_DIV4   0 /* SPI Master mode, clock = FOSC/4 */ 
#define SPI_MASTER_FOSC_DIV16  1 /* SPI Master mode, clock = FOSC/16 */ 
#define SPI_MASTER_FOSC_DIV64  2 /* SPI Master mode, clock = FOSC/64 */
#define SPI_MASTER_FOSC_TMR2   3 /* SPI Master mode, clock = TMR2 output/2 */
#define SPI_SLAVE_SS_ENABLE    4 /* SPI Slave mode, clock = SCK pin, SS pin control enabled */
#define SPI_SLAVE_SS_DISABLE   5 /* SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin */

/* Clock Polarity Select */
#define SPI_IDLE_STATE_HIGH_LEVEL   1 /* Idle state for clock is a high level */
#define SPI_IDLE_STATE_LOW_LEVEL    0 /* Idle state for clock is a low level */

/* SPI Clock phase Select */
#define SPI_TRANSMIT_ACTIVE_TO_IDLE 1 /* Transmit occurs on transition from active to Idle clock state */
#define SPI_TRANSMIT_IDLE_TO_ACTIVE 0 /* Transmit occurs on transition from Idle to active clock state */

/* SPI Sample Select */
#define SPI_DATA_SAMPLE_END         1 /* Input data sampled at end of data output time */
#define SPI_DATA_SAMPLE_MIDDLE      0 /* Input data sampled at middle of data output time */

/* ----------------- Macro Functions Declarations -----------------*/
/* Master Synchronous Serial Port Enable */
#define SPI_ENABLE_MODULE()    (SSPCON1bits.SSPEN=1) /* Enables serial port and configures SCK, SDO, SDI and SS as serial port pins */
#define SPI_DISABLE_MODULE()   (SSPCON1bits.SSPEN=0) /*  Disables serial port and configures these pins as I/O port pins */

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    #if SPI_INTERRUPT_FEATURE==ENABLE
    void (* SPI_InterruptHandler)(void);
    interrupt_priority_t priority;
    #endif
    uint8 spi_mode  :4;
    uint8 clock_polarity :1;
    uint8 clock_phase :1;
    uint8 sample :1;
}spi_config_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType SPI_Init(const spi_config_t *_spi);
Std_ReturnType SPI_DeInit(const spi_config_t *_spi);
Std_ReturnType SPI_Send_Byte(const spi_config_t *_spi, const uint8 _data);
Std_ReturnType SPI_Read_Byte(const spi_config_t *_spi, uint8 *_data);
Std_ReturnType SPI_Send_Byte_NonBlocking(const spi_config_t *_spi, const uint8 _data);
Std_ReturnType SPI_Read_Byte_NonBlocking(const spi_config_t *_spi, uint8 *_data);
#endif	/* SPI_H */

