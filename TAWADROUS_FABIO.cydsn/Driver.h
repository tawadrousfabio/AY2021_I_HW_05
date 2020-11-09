/**
*   \brief Header code for the Driver.
*   \author: Fabio Tawadrous
*   
*/
#ifndef _RG_LED_DRIVER_H_
    #define _RG_LED_DRIVER_H_
    #include "project.h"
    
    
    
    #define STARTUP_REGISTER_ADDRESS 0x0000  //address of the startup register in the EEPROM
    
    /**
    *   \brief Address of the Control register 1
    */
    #define LIS3DH_CTRL_REG1 0x20

    /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18
    
    
    /**
    *   \brief Struct holding the patterns data
    */
    
    
    typedef struct {
        uint8_t frequency;    
    } Config;
    
    
    
    /**
    *   \brief 
    */
    uint8_t EEPROM_Register_Check(void);
    
    void Write_reg1_freq(Config c, uint8_t k);
#endif

/* [] END OF FILE */
