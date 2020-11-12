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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    UART_Debug_Start();
    EEPROM_Start();
    I2C_Peripheral_Start();
    
    BTN_ISR_StartEx(Custom_ISR_BTN);   // Start the ISR
    
    //Device connection
    Connection();
    
    /*      EEPROM CHECK        */
    k = EEPROM_ReadByte(STARTUP_REGISTER_ADDRESS);
    if (k<0 | k>5) k = 0; 
    //This control is used because the first time I run the device, I don't know 
    //which value is stored inside the 0x0000 address of the EEPROM. This may cause a crash of the application,
    //or generate an error. In order to avoid this, if k is not between 0 and 5, k will be imposed as 0.
    
    Write_reg1_freq(CFG_ARR[k], k); //Set the frequency related to the last k (no more necessary)
    
    /*      REG4 - HIGH RESOLUTION SETTING        */
    if (ctrl_reg4 != LIS3DH_CTRL_REG4_HR)
    {
        ctrl_reg4 = LIS3DH_CTRL_REG4_HR; // HIGH RESOLUTION
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG4,
                                             ctrl_reg4);
        
          
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                            LIS3DH_CTRL_REG4,
                                            &ctrl_reg4);
        
        
        if (error == NO_ERROR)
        {
            sprintf(message, "CONTROL REGISTER 4: 0x%02X\r\n", ctrl_reg4);
            UART_Debug_PutString(message); 
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to read control register4\r\n");   
        }
        
        
    }
    
    Output_Array[0] = HEADER;
    Output_Array[7] = FOOTER;

    for(;;)
    {
        //When the button is pressed
        if (REG1_set_freq_flag)
        {
            //Write the frequency and store k
            Write_reg1_freq(CFG_ARR[k], k); 
            REG1_set_freq_flag = 0;
        }

        /*      I2C Reading Status Register       */
        uint8_t status_register; 
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                            LIS3DH_STATUS_REG,
                                            &status_register);
        
        if (error == NO_ERROR)
        {
            /*  Enable only for debug purposes  
              
              sprintf(message, "STATUS REGISTER: 0x%02X\r\n", status_register);
              UART_Debug_PutString(message); 
            
            */
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to read status register\r\n");   
        }
        
        
        /*      New data arrived       */
    
        if(status_register &= LIS3DH_STATUS_REG_ACC_COMING_VALUE)  //0x08 xxxxxxxx 000001000
        {
            errorf = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_X_L, 
                                                    6,
                                                    Acceleration_Data_Array);
            if (errorf == NO_ERROR)
            {
                //Since the return values is no needed for this specific applicatio, I will not save them in variables
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
