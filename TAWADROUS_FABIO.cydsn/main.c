/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "InterruptRoutines.h"
#include "stdio.h"
#include "ErrorCodes.h"
#include "I2C_Interface.h"
#include "configs.h"

extern uint8_t REG1_set_freq_flag;

extern uint8_t k;

char message[50] = {'\0'};
uint8_t ctrl_reg4;
ErrorCode error, errorf;
uint8_t status_register = 0x00;
#define DEBUG_ENABLED 1
#define DEBUG_DISABLED 0


int main(void)
{
    CyGlobalIntEnable; 

    UART_Debug_Start();
    EEPROM_Start();
    I2C_Peripheral_Start();
    
    BTN_ISR_StartEx(Custom_ISR_BTN);  
    
    
    Connection();                                      //   Device connection
    k = EEPROM_ReadByte(STARTUP_REGISTER_ADDRESS);     //   Read the last frequency used.
    if ((k<0) | (k>5)) k = 0;                          //   Control to avoid unexpected value the very first time I program the PSoC
    
    Write_reg1_freq(CFG_ARR[k], k);                    //   Set the frequency related to the last k
    
    
    /*      REG4 - HIGH RESOLUTION SETTING        */
    if (ctrl_reg4 != LIS3DH_CTRL_REG4_HR)
    {
        ctrl_reg4 = LIS3DH_CTRL_REG4_HR; // HIGH RESOLUTION
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG4,
                                             ctrl_reg4);
        
        Debug(ctrl_reg4, LIS3DH_CTRL_REG4, "control register 4", DEBUG_ENABLED);
    }
    
    Output_Array[0] = HEADER;
    Output_Array[7] = FOOTER;

    for(;;)
    {
        if (REG1_set_freq_flag)                 //  i.e. button pressed
        {
            Write_reg1_freq(CFG_ARR[k], k);     //   Write the frequency and store k
            REG1_set_freq_flag = 0;             //   Flag reset
        }

        
        
        status_register = Debug(status_register, LIS3DH_STATUS_REG, "status register", DEBUG_DISABLED);  //  Read the status register.
    
        if(status_register &= LIS3DH_STATUS_REG_ACC_COMING_VALUE)  
        {
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_X_L, 
                                                    6,
                                                    Acceleration_Data_Array);
            if (error == NO_ERROR)
            {
                Generic_Output_Axys_Acceleration(STARTING_INDEX_X);  
                Generic_Output_Axys_Acceleration(STARTING_INDEX_Y);
                Generic_Output_Axys_Acceleration(STARTING_INDEX_Z);
                UART_Debug_PutArray(Output_Array, 8);
            }
            else{
                UART_Debug_PutString("Error occurred during I2C comm to read acceleration output registers\r\n");   
            }
        }
    }
}

/* [] END OF FILE */
