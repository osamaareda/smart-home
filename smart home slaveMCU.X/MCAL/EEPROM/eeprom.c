/* 
 * File:   eeprom.c
 * Author: osama reda
 *
 * Created on October 21, 2023, 11:26 PM
 */
#include"eeprom.h"
/**
 * @brief  : writes a data byte to given Data EEPROM location
 * @param  : bAdd -> Data EEPROM location to which data to be written
 * @param  : bData -> Data to be written to Data EEPROM location
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 * @Example ret = EEPROM_WriteByte(0x3ff, 0);
 */
#if EEPROM_CONFIG==ENABLE
Std_ReturnType EEPROM_WriteByte(uint16 bAdd, uint8 bData){
     Std_ReturnType ret = E_OK;
    //Read the Interrupt Status "Enabled or Disabled"
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    //Update the Address Registers 
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
    //Update the Data Register 
    EEDATA = bData;
    //Select Access data EEPROM memory 
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    //Allows write cycles to Flash program/data EEPROM 
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    //Disable all interrupts "General Interrupt" 
    INTERRUPT_GlobalInterruptDisable();
    //Write the required sequence : 0x55 -> 0xAA
    EECON2 = 0x55;
    EECON2 = 0xAA;
    //Initiates a data EEPROM erase/write cycle 
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    //Wait for write to complete 
    while(EECON1bits.WR);
    //Inhibits write cycles to Flash program/data EEPROM
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    //Restore the Interrupt Status "Enabled or Disabled" 
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}
#endif
/**
 * @brief  : reads a data byte from given Data EEPROM location
 * @param  : bAdd -> Data EEPROM location from which data has to be read
 * @param  : bData -> Data byte read from given Data EEPROM location
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 * @Example ret = EEPROM_ReadByte(0x3ff,&var);
 */
#if EEPROM_CONFIG==ENABLE
Std_ReturnType EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==bData){
        ret=E_NOT_OK;
    }
    else{
        //Update the Address Registers 
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        //Select Access data EEPROM memory
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        //Initiates a data EEPROM read cycle 
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP(); //NOPs may be required for latency at high frequencies 
        NOP(); //NOPs may be required for latency at high frequencies
        //Return data
        *bData = EEDATA;
        ret=E_OK;
    }
    
    return ret;
}
#endif