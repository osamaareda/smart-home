/* 
 * File:   eeprom.h
 * Author: osama reda
 *
 * Created on October 21, 2023, 11:26 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/*-----------------------includes-------------------------*/
#include"../mcal_std_types.h"
#include"mcal_eeprom_cfg.h"
#include"../INTERRUPT/mcal_external_interrupt.h"
  
/* ----------------- Macro Declarations -----------------*/
/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY       1
#define ACCESS_EEPROM_PROGRAM_MEMORY      0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS           1
#define ACCESS_FLASH_EEPROM_MEMORY        0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
/* Read Control */
#define INITIATE_DATA_EEPROM_READ         1

/*----------------function declaration-----------------*/
Std_ReturnType EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType EEPROM_ReadByte(uint16 bAdd, uint8 *bData);
#endif	/* EEPROM_H */