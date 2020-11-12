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


void Connection(void)
{
    char message[50] = {'\0'};
    
    CyDelay(100);
    
    uint32_t rval;
 
	// Setup the screen and print the header
	UART_Debug_PutString("\n\n   ");
	for(uint8_t i = 0; i<0x10; i++)
	{
        sprintf(message, "%02X ", i);
		UART_Debug_PutString(message);
	}
    
    for(uint8_t i2caddress = 0; i2caddress < 0x80; i2caddress++)
	{
		if(i2caddress % 0x10 == 0 )
        {
            sprintf(message, "\n%02X ", i2caddress);
		    UART_Debug_PutString(message);
        }
 
		rval = I2C_Master_MasterSendStart(i2caddress, I2C_Master_WRITE_XFER_MODE);
        
        if(rval == I2C_Master_MSTR_NO_ERROR) // If you get ACK then print the address
		{
            sprintf(message, "%02X ", i2caddress);
		    UART_Debug_PutString(message);
		}
		else //  Otherwise print a --
		{
		    UART_Debug_PutString("-- ");
		}
        I2C_Master_MasterSendStop();
	}
	UART_Debug_PutString("\n\n");

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
            
            //Write the k value associated to the frequency in the EEPROM
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(k, STARTUP_REGISTER_ADDRESS);
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");  
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
    
    return acceleration; //return the acceleration value converted and scaled. Not 
}

uint8_t Debug(uint8_t data, uint8_t reg_address, char name[20], uint8_t debug_state)
{
    char message[50] = {'\0'};
    ErrorCode e;
        
    e = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        reg_address,
                                        &data);
    if (debug_state)
    {
        if (e == NO_ERROR)
        {
            sprintf(message, "Value of %s :  0x%02X\r\n", name, data);
            UART_Debug_PutString(message); 
        }
        else
        {
            sprintf(message, "Error occurred during I2C comm to read %s ", name);
            UART_Debug_PutString(message); 
        }
    }
    
    return data;
}
/* [] END OF FILE */
