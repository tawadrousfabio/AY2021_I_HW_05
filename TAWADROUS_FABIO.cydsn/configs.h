/**
*   \brief Header containing the configs information
*   \author: Fabio Tawadrous
*
*/

#include "Driver.h"
/**
*   \brief Hex value to set normal mode to the accelerator
*/
#define LIS3DH_NORMAL_MODE_CTRL_REG1_1H 0x17

#define LIS3DH_NORMAL_MODE_CTRL_REG1_10H 0x27

#define LIS3DH_NORMAL_MODE_CTRL_REG1_25H 0x37

#define LIS3DH_NORMAL_MODE_CTRL_REG1_50H 0x47

#define LIS3DH_NORMAL_MODE_CTRL_REG1_100H 0x57

#define LIS3DH_NORMAL_MODE_CTRL_REG1_200H 0x67



const Config CFG_ARR[6] = {{LIS3DH_NORMAL_MODE_CTRL_REG1_1H},
                           {LIS3DH_NORMAL_MODE_CTRL_REG1_10H},
                           {LIS3DH_NORMAL_MODE_CTRL_REG1_25H},
                           {LIS3DH_NORMAL_MODE_CTRL_REG1_50H},
                           {LIS3DH_NORMAL_MODE_CTRL_REG1_100H},
                           {LIS3DH_NORMAL_MODE_CTRL_REG1_200H}};

/* [] END OF FILE */
