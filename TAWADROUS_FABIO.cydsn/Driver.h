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
    *   \brief Address of the Control register 4
    */
    #define LIS3DH_CTRL_REG4 0x23

    #define LIS3DH_CTRL_REG4_HR 0x88 //10001000  (BDU 0 FS1,2 HR 000)
    
    
    /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18
    
    /**
    *   \brief Address of the Status register
    */
    #define LIS3DH_STATUS_REG 0x27
    
    #define LIS3DH_STATUS_REG_ACC_COMING_VALUE 0x08
    
    
    #define LIS3DH_OUT_X_L 0x28
    
    #define LIS3DH_OUT_Y_L 0x2A
    
    #define LIS3DH_OUT_Z_L 0x2C
    
    #define LIS3DH_OUT_X_H 0x29
    
    #define LIS3DH_OUT_Y_H 0x2B
    
    #define LIS3DH_OUT_Z_H 0x2D
    
    #define STARTING_INDEX_X 0
    
    #define STARTING_INDEX_Y 2
    
    #define STARTING_INDEX_Z 4
    

    
    #define HEADER 0xA0
    #define FOOTER 0xC0
    
    
    
    uint8_t Acceleration_Data_Array[6];
    uint8_t Output_Array[8];
    /**
    *   \brief Struct holding the patterns data
    */
    typedef struct {
        uint8_t frequency;    
    } Config;
    
    
    void Connection(void);
    
    /**
    *   \brief 
    */
    uint8_t EEPROM_Register_Check(void);
    
    /**
    *   \brief 
    */
    void Write_reg1_freq(Config c, uint8_t k);
    

    
    /**
    *   \brief used to output any axys acceleration
    */
    int16 Generic_Output_Axys_Acceleration(uint8_t buffer_starting_index);
    
    
#endif

/* [] END OF FILE */
