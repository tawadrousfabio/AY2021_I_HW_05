/**
*   \file main.c
*   \brief Project aim: to print a 3-axys accelerometer output at a specific frequency in the range 1-200Hz, and to use the I2C protocol. 
*   \author: Fabio Tawadrous
*/


#include "project.h"
#include "InterruptRoutines.h"
#include "stdio.h"
#include "ErrorCodes.h"
#include "I2C_Interface.h"
#include "Driver.h"

extern uint8_t REG1_set_freq_flag, k;

uint8_t ctrl_reg4;
ErrorCode error;
uint8_t status_register = 0x00;


int main(void)
{
    CyGlobalIntEnable; 
    
    //  Component initialization
    
    UART_Debug_Start();
    EEPROM_Start();
    I2C_Peripheral_Start();
    
    BTN_ISR_StartEx(Custom_ISR_BTN);  
    
    
    Connection();                                      //   Device connection
    k = EEPROM_ReadByte(STARTUP_REGISTER_ADDRESS);     //   Read the last frequency used.
    if ((k<0) | (k>5)) k = 0;                          //   Control to avoid unexpected value the very first time the PSoC is programmed
    
    Write_reg1_freq(k);                                //   Set the frequency related to k
    
    
    
    if (ctrl_reg4 != LIS3DH_CTRL_REG4_HR)
    {
        ctrl_reg4 = LIS3DH_CTRL_REG4_HR;               //   Set the HR only if not already set
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG4,
                                             ctrl_reg4);
        
        Debug(ctrl_reg4, LIS3DH_CTRL_REG4, "control register 4", DEBUG_DISABLED);   //    Set debug enabled if needed.
    }
    
    Output_Array[0] = HEADER;                          // Header of the output array
    Output_Array[7] = FOOTER;                          // Tail of the output array

    for(;;)
    {
        if (REG1_set_freq_flag)                        //  i.e. button pressed
        {
            Write_reg1_freq(k);                        //   Write the frequency on reg1 and store k
            REG1_set_freq_flag = 0;                    //   Flag reset
        }

        
        //  Read the status register 
        status_register = Debug(status_register, LIS3DH_STATUS_REG, "status register", DEBUG_DISABLED);  
    
        if(status_register &= LIS3DH_STATUS_REG_ACC_COMING_VALUE)              //   If new data arrive
        {
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,    //   Then read them
                                                    LIS3DH_OUT_X_L, 
                                                    6,
                                                    Acc_Data_Array);
            if (error == NO_ERROR)
            {
                Generic_Output_Axys_Acceleration(STARTING_INDEX_X);             //   convert and store the X axys data in the output array
                Generic_Output_Axys_Acceleration(STARTING_INDEX_Y);             //   convert and store the Y axys data
                Generic_Output_Axys_Acceleration(STARTING_INDEX_Z);             //   convert and store the Z axys data
                UART_Debug_PutArray(Output_Array, 8);                           //   Print the result
            }
            else{
                UART_Debug_PutString("Error occurred during I2C comm to read acceleration output registers\r\n");   
            }
        }
    }
}

/* [] END OF FILE */
