/**
*   \brief Source code for the Driver.
*   \author: Fabio Tawadrous
*   
*   In this file what were defined in the driver header file
*   is being implemented.
*/

#include "Driver.h"
#include "I2C_Interface.h"
#include "stdio.h"

uint8_t ctrl_reg1;

/**
*   \brief 
*/

void Components_Initialization(void)
{ 
	UART_Debug_Start(); 
}


/**
*   \brief 
*/

uint8_t EEPROM_Register_Check(void){
    
    //check register
    //EEPROM_UpdateTemperature();
    
    uint8_t f =  EEPROM_ReadByte(STARTUP_REGISTER_ADDRESS);
    
    //if(f<0) f = 1;
    
    return f-1;

}


void Write_reg1_freq(Config c, uint8_t k){
    
    ErrorCode error_reg1;
    // String to print out messages on the UART
    char message[50] = {'\0'};
    //UART_Debug_PutString("\r\nWriting new values..\r\n");
    
    //This if statement is no more useful, since this condition will never happen.
    
    //if (ctrl_reg1 != c.frequency)
    //{
    
    
        ctrl_reg1 = c.frequency;
                
        error_reg1 = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                         LIS3DH_CTRL_REG1,
                                                         ctrl_reg1);
                

        if (error_reg1 == NO_ERROR)
        {
            sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
            //UART_Debug_PutString(message); 
            
            //Write the k value associated with the frequency in the EEPROM
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(k, STARTUP_REGISTER_ADDRESS);
            
        }
        else
        {
         //   UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");  
        }
        
        
        
    //}
    
}



int16 Generic_Output_Axys_Acceleration(uint8_t buffer_starting_index)
{
    int16 acceleration;
    float acceleration_conv;
    int16 dt = 1000;
    
    
    acceleration = (int16)((Acceleration_Data_Array[buffer_starting_index] | (Acceleration_Data_Array[buffer_starting_index+1]<<8)))>>4;
    acceleration_conv = acceleration * (2*9.81)/2048.0;
    acceleration = (int16)(acceleration_conv * dt);
    
    Output_Array[buffer_starting_index +1] = (uint8_t) (acceleration & 0xFF);
    Output_Array[buffer_starting_index +2] = (uint8_t) (acceleration >>  8);
    
    if(Output_Array[0] != HEADER) Output_Array[0] = HEADER;
    if(Output_Array[7] != FOOTER) Output_Array[0] = FOOTER;
    
    
    return acceleration; //return the acceleration value converted and scaled. Not 
}
/* [] END OF FILE */
