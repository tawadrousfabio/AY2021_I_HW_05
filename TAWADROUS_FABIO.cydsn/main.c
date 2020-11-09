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
//#include "configs.h"
#include "stdio.h"
#include "ErrorCodes.h"
#include "I2C_Interface.h"
#include "configs.h"

extern uint8_t REG1_set_freq_flag;
//extern uint8_t k;

extern uint8_t k;



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

   
    
    UART_Debug_Start();
    EEPROM_Start();
    I2C_Peripheral_Start();
    
    BTN_ISR_StartEx(Custom_ISR_BTN);   // Start the ISR
    
        

    /*      EEPROM CHECK        */
    k = EEPROM_Register_Check(); //Retrieve the last k from the EEPROM
    Write_reg1_freq(CFG_ARR[k], k); //Set the frequency related to the last k
    
            
    for(;;)
    {
        

        //When the button is pressed
        if (REG1_set_freq_flag==1)
        {
            //Write the frequency and store k
            Write_reg1_freq(CFG_ARR[k], k); 
            REG1_set_freq_flag = 0;
        }
        
        

        
    }
}

/* [] END OF FILE */
