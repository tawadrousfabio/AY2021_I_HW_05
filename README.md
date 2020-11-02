# Electronic Technologies and Biosensors Laboratory
## Academic Year 2020/2021 - I Semester
---
## Assignment 05
This repository contains the PSoC Creator workspace to be used as a starting point for the successful submission of the Assignment 05 of the course "Electronic Technologies and Biosensors Laboratory" of the I Semester of the academic year 2020/2021.

---
### Objective
In this assignment you are required to create a project using PSoC Creator and the CY8CKIT-059 KIT along with the following components:
-	LIS3DH 3-Axis Accelerometer breakout board

### Context
LTEBS srl is testing I2C bus protocol on reasonable priced breakout boards, the company wants to verify the expected behaviour of a LIS3DH breakout at different frequencies. Your ability to correctly interpret a component datasheet will be required!

- At startup, the microcontroller will check an internal EEPROM "startup" register to select a sampling frequency for the LIS3DH Accelerometer.
- Correctly set the control registers to output 3-axis signals in High Resolution Mode at the selected frequency (previously read).
- The user can cycle through known sampling frequencies (1÷200Hz) via the press of the microcontroller push button. Consequently, both the LIS3DH and the internal "startup"(EEPROM) registers must be set appropriately to match the required value.
- Data must be read from the 3-axis registers at a sufficient rate. Every read must provide unique data (i.e. checking the status register).
- Every axis acceleration must be properly read and converted to m/s^2 values.
- Data must be accurately plot from the Bridge Control Panel (keeping at least 3 digits). It is required to provide the Bridge Control Panel .ini and .iic file for interfacing with the firmware (NB: all 3-axial signals must be plotted)

### Connections
The I2C Protocol requires pins **12.0** and **12.1**.
The UART must use the pins **12.6** and **12.7** in order to communicate through the KitProg.

### Serial Port Communication
The acceleration values must be sent to the BCC via UART communication. The Baudrate of such communication must be sufficient to avoid hiccups in the data package delivery (JUSTIFY YOUR CHOICE IN THE TOP DESIGN DOCUMENTATION).
This means that if the microcontroller is, for instance, reading at 200Hz from the LIS3DH accelerometer, the BCC must receive a stable 200 packages per second (±2 package/s is not considered a relevant variation).
You will have to think about package size in relation to your comms speed.

### Setup and Assignment Delivery
- Fork this repository
- Clone the repository you just forked by entering the following command in your terminal:

    `git clone https://github.com/[your_username]/AY2021_I_HW_05.git`
- Open up the workspace in PSoC Creator
- Activate the project with your name and surname
- Work on your project. Remember to save Bridge Control Panel configuration files (.ini and .iic) inside BRIDGE_CONTROL_PANEL_CONFIG_FILES folder inside your project folder
- The last commit must be named '*SURNAME_NAME* Final Delivery'
- Propose a pull request before the deadline for the assignment, which is on **November 14 at 12AM**


### Evaluation
The evaluation of the assignment will take into consideration the following aspects of the project:
- successful build process without any warning/error generated
- successful programming without any error generated
- correct functioning of the device as per the requirements
- code organization (header and source files, useful comments)
- schematic organization and documentation
- successful use of git for version control (commits with proper comments, use of branches, ...)
- successful pull request on GitHub


### Additional Resources:
- [PSoC PWM Component Datasheet](https://www.cypress.com/file/376411/download)
- [PSoC 5LP Interrupts](https://www.cypress.com/file/44256/download)
- [PSoC 101 Video Tutorial](https://www.youtube.com/watch?v=LrXXpQr1itY&list=PLX6sqqUB8iOjsMfGEDcsPSuYLEFCh50Hr)
