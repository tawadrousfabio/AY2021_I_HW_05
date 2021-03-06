/**
*   \brief Header code for the Driver.
*   \author: Fabio Tawadrous
*   
*/
#ifndef _RG_LED_DRIVER_H_
    #define _RG_LED_DRIVER_H_
    #include "project.h"
    
    
    /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18
    
    
    /**
    *   \brief Addresses of registers
    */
    #define LIS3DH_CTRL_REG1         0x20
    #define LIS3DH_CTRL_REG4         0x23
    #define LIS3DH_STATUS_REG        0x27
    
    
    /**
    *   \brief EEPROM address where frequency is stored
    */
    #define STARTUP_REGISTER_ADDRESS 0x0000  

    
    /**
    *   \brief Allows to set the High resolution on reg4
    */
    #define LIS3DH_CTRL_REG4_HR 0x88 
    
    
    /**
    *   \brief Allows to catch new data in the status reg
    */
    #define LIS3DH_STATUS_REG_ACC_COMING_VALUE 0x08
    
    
    /**
    *   \brief Output register addresses
    */
    #define LIS3DH_OUT_X_L 0x28
    
    #define LIS3DH_OUT_Y_L 0x2A
    
    #define LIS3DH_OUT_Z_L 0x2C
    
    #define LIS3DH_OUT_X_H 0x29
    
    #define LIS3DH_OUT_Y_H 0x2B
    
    #define LIS3DH_OUT_Z_H 0x2D
    
    
    /**
    *   \brief Starting indexes in the data array axys-specific
    */
    #define STARTING_INDEX_X 0
    
    #define STARTING_INDEX_Y 2
    
    #define STARTING_INDEX_Z 4
    
    
    /**
    *   \brief Header and tail of the output array
    */
    #define HEADER 0xA0
    #define FOOTER 0xC0
    
    /**
    *   \brief debug state in the Debug() function
    */
    #define DEBUG_ENABLED 1
    #define DEBUG_DISABLED 0

    /**
    *   \brief Set normal mode to the accelerator and specific frequencies
    */
    #define LIS3DH_NORMAL_MODE_CTRL_REG1_1H 0x17    //  1Hz

    #define LIS3DH_NORMAL_MODE_CTRL_REG1_10H 0x27   //  10Hz

    #define LIS3DH_NORMAL_MODE_CTRL_REG1_25H 0x37   //  25Hz

    #define LIS3DH_NORMAL_MODE_CTRL_REG1_50H 0x47   //  50Hz

    #define LIS3DH_NORMAL_MODE_CTRL_REG1_100H 0x57  //  100Hz

    #define LIS3DH_NORMAL_MODE_CTRL_REG1_200H 0x67  //  200Hz
    
    
    /**
    *   \brief acceleration data and output arrays
    */    
    uint8_t Acc_Data_Array[6];
    uint8_t Output_Array[8];
    
    
    /**
    *   \brief check the device connection (Credits Davide Marzorati)
    */
    void Connection(void);
    
    
    /**
    *   \brief write the frequency on the reg1 and store it in the EEPROM
    */
    void Write_reg1_freq(uint8_t k);
    
    
    /**
    *   \brief used to give as output any axys acceleration (depending on the input)
    */
    int16 Generic_Output_Axys_Acceleration(uint8_t buffer_starting_index);
    
    
    /**
    *   \brief used to debug the registers and, if needed, to print the result
    */
    uint8_t Debug(uint8_t data, uint8_t reg_address, char name[20], uint8_t debug_state);
    
#endif

/* [] END OF FILE */
