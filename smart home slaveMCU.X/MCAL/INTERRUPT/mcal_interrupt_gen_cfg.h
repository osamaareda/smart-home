/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: 20128
 *
 * Created on October 8, 2023, 12:58 AM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/*----------------macros declaration-----------------*/

#define ENABLE                               1
#define DISABLE                              0 
#define INTERRUPT_PRIORITY_LEVELS            DISABLE
#define EXTERNAL_INTERRUPT_INTx_FEATURE      ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE  ENABLE
#define ADC_INTERRUPT_FEATURE                ENABLE
#define TIMER0_INTERRUPT_FEATURE             ENABLE
#define TIMER1_INTERRUPT_FEATURE             ENABLE
#define TIMER2_INTERRUPT_FEATURE             ENABLE
#define TIMER3_INTERRUPT_FEATURE             ENABLE
#define CCP1_INTERRUPT_FEATURE               ENABLE
#define CCP2_INTERRUPT_FEATURE               ENABLE
#define EUSART_TX_INTERRUPT_FEATURE          ENABLE
#define EUSART_RX_INTERRUPT_FEATURE          ENABLE
#define SPI_INTERRUPT_FEATURE                ENABLE
#define I2C_INTERRUPT_FEATURE                ENABLE
#define I2C_BUS_COL_INTERRUPT_FEATURE        ENABLE
#endif	/* MCAL_INTERRUPT_GEN_CFG_H */