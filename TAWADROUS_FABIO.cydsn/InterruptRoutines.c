/**
*   \brief Source code for the implementation of what happens during the interrupt
*   \author: Fabio Tawadrous
*/
#include "InterruptRoutines.h"
#include "stdio.h"

uint8 k = -1; //k is an index that refers to the array of patterns

uint8_t REG1_set_freq_flag = 0;

CY_ISR(Custom_ISR_BTN)
{
    
    k++; //If the button is pressed, k is incremented.
    REG1_set_freq_flag = 1;
    
    On_Board_LED_Write(1);
    
    if(k>5) 
    {
        k=0; 
        On_Board_LED_Write(0);
        
    } 
    
 }


/* [] END OF FILE */
