# TivaC_TM4C123G
### GitHub :octocat: Codes for Texas Instruments EK-TM4C123GXL Launchpad :alien: ###

### Labwork for SF State ENGR 478 ###

#### Lab 2 ####
* Add a new function to the sample program (sim) which compares the values of NUM1 and NUM2 and stores the larger value into a new variable bit LARGER. You need to:
  * Define a new 32-bit LARGER
  * Design a subroutine GET_LARGER, draw the flowchart of the subroutine, and write assembly code to implement this subroutine.
  
#### Lab 3 ####
* Modify the C program in the project my_switch created by yourself in Section C. In the modified system, when SW2 (connected with PF0) is pressed, the red LED (connected with PF1) is turned off, otherwise the red LED is on.
  * The flow chart of the system 
  * Explanation of your modifications 
  * The C program listing with detailed comments for each line of code.  
  * The execution results of your program (your observations).
* Create a new project my_toggle by following the instructions of creating a new project in Section C. Copy the code in the file toggle.c in the sample project toggle and paste it in your created project. Modify the code to make the green LED (connected with PF3) flash. Also try to make the LED flash 5 times slower.
  * The flow chart of the system 
  * Explanation of your modifications 
  * The C program listing with detailed comments for each line of code.
  * The execution results of your program (your observations).

#### Lab 4 ####
* Create and implement two new projects my_switch_PinMux and my_toggle_PinMux, which perform the same functions as my_switch and my_toggle did, respectively. my_switch and my_toggle are the two projects you implemented in Lab 3. In my_switch_PinMux, when SW2 (connected with PF0) is pressed, the red LED (connected with PF1) is turned off, otherwise the red LED is on. my_toggle_PinMux makes the green LED (connected with PF3) flash. In this lab, you have to use PinMux to initialize the ports and use GPIOPinRead/GPIOPinWrite functions to configure the GPIO data registers. In your lab report, for each project, please include the following:
  * The C program listing with detailed comments for each line of code.
  * The execution results of your program (your observations).
  
  #### Lab 5 ####
* The system has one input switch (SW1) and two output LEDs (red and blue LEDs). Overall functionality of this system is described in the following rules. Included in the lab work is a flowchart.
  * If SW1 is pressed, then the blue LED will be turned off, and the red LED will be toggled every half second. 
  * If SW1 is not pressed, then the red LED will be off, and the blue LED will be toggled every half second. Basically you need to figure out which IO ports you need to configure, and how to configure them. You also need to know how to implement specific delay, looping, and if/then. 
