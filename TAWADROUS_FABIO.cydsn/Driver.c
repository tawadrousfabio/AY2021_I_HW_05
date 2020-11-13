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

//  Array with the sampling frequencies 
uint8_t Configs[6] = { LIS3DH_NORMAL_MODE_CTRL_REG1_1H,
                    LIS3DH_NORMAL_MODE_CTRL_REG1_10H,
                    LIS3DH_NORMAL_MODE_CTRL_REG1_25H,
                    LIS3DH_NORMAL_MODE_CTRL_REG1_50H,
                    LIS3DH_NORMAL_MODE_CTRL_REG1_100H,
                    LIS3DH_NORMAL_MODE_CTRL_REG1_200H};



/**
*   \brief This function writes the frequency value on the register 1, and saves the value in the EEPROM 
*/

void Write_reg1_freq(uint8_t k){
    
    ErrorCode error_reg1;
    
    if (ctrl_reg1 != Configs[k])
    {
        ctrl_reg1 = Configs[k];
                
        error_reg1 = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1); 

        if (error_reg1 == NO_ERROR)
        {
            EEPROM_UpdateTemperature();     //  needed before storing a new value
            EEPROM_WriteByte(k, STARTUP_REGISTER_ADDRESS);     
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");  
        }
        
        Debug(ctrl_reg1, LIS3DH_CTRL_REG1, "control register 1", DEBUG_DISABLED);   //  Read reg1 value
    }
}


/**
*
*  This is a generic function valid for each axys so that I can recall it 3 times
*  (one for the x axys, one for y and one for z), by just giving in input the starting
*  index of the buffer array. 
*  As we can see from the datasheet, the high resolution has 12bits, so we need a shift
*  of 4 bits. After this, we make the conversion in m/s^2 and store the value in the output
*  array. 
*
*  Note: I decided to return the acceleration converted and scaled, so that if this value is
*  needed for other purposes it can be used and stored in a variable. In our case this 
*  phase is not necessary, so the function will be called 3 times, without storing the 
*  return value. 
*
*/
int16 Generic_Output_Axys_Acceleration(uint8_t buffer_starting_index)
{
    int16 acceleration;
    float acceleration_conv;
    int16 dt = 1000;
    
    
    acceleration = (int16)((Acc_Data_Array[buffer_starting_index] | (Acc_Data_Array[buffer_starting_index+1]<<8)))>>4;
    acceleration_conv = acceleration * (2*9.81)/2048.0;  //  2048 = 2^12 / 2 (because of the sign), FS = +/- 2g
    acceleration = (int16)(acceleration_conv * dt);
    
    Output_Array[buffer_starting_index +1] = (uint8_t) (acceleration & 0xFF);
    Output_Array[buffer_starting_index +2] = (uint8_t) (acceleration >>  8);
    
    return acceleration; 
}

/**
*
*  This is a generic function valid for each register. It could be used for debug 
*  purposes. In particular, it takes as input the specific data of the register,
*  the register address, a "name" used in the sprintf function, and a debug state.
*  This last variable can be set as 1 (debug active) or 0 (debug unactive). 
*  When the debug is unactive, there will not be printed any message in cool
*  term. By default I recalled this function every time with disabled debug, also
*  to avoid the saturation of the UART bandwidth.
*
*  Note: I had to add the return statement because of a bug in the reading of the status register.
*
*/
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


/**
*   \brief function used to test the connection, and see which is the address of the connected device 
*
*   \credits: Davide Marzorati
*/
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
/* [] END OF FILE */
