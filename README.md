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

#### Lab 6 ####
* The system consists of two LaunchPads as shown in Figure 1. Device A and Device B are connected using two male-male wires (Figure 2). The output port PF2 on Device A is connected with the input port PA7 on Device B. The ground pins on both devices are also connected. You need to develop two software projects in this lab, one for each device.
  * Software on Device A: The system implements a 2-bit rotary counter on Device A.
The system has two input switches (SW1 (PF4) and SW2 (PF0)) and two output LEDs
(red (PF1) and blue (PF2) LEDs). Overall functionality of this system is described in the
following rules:
     * The red LED is used to display bit 0 of the counter; the blue LED is used to display bit 1.
     * The system starts with the counter equal to 0.
     * If SW1 is pressed, the counter is incremented by 1; If SW2 is pressed, the counter is decremented by 1. Both SW1 and SW2 generate edge-triggered interrupts to update the counter.
  * Software on Device B: The system has one input port (PA7) and one output port (PF3, green LED). Overall functionality of this system is described in the following rules. 
     * The system starts with the green LED off. 
     * The value change on PA7 generates edge-triggered interrupt to toggle PF3. When the value on PA7 changes from 1 to 0 or from 0 to 1 (the value of PA7 on Device B changes with the value of PF2 on Device A), the green LED will be toggled once.

#### Lab 7 ####
* Implement a 2-bit rotary counter on the TM4C microcontroller. The counter is controlled by two types of interrupts simultaneously. 1) Edge-triggered interrupt – the counter is incremented by 1 when SW1 is pressed and decremented by 1 when SW2 is pressed. 2) Periodic interrupt – the counter is incremented by 1 periodically every 1 second. The periodic interrupt has a higher priority than the edge-triggered interrupts. Two on-board LEDs are used to display the counter.
* System Requirements: The system has two input switches (SW1 (PF4) and SW2 (PF0)) and two output LEDs (red (PF1) and blue (PF2) LEDs). Overall functionality of this system is described in the following rules.
     * The red LED is used to display bit 0 of the counter; the blue LED is used to display bit 1.
     * The system starts with the counter equal to 0. 
     * The counter increments by 1 every one second. The general purpose timer TIMER0 is used to generate this periodic one second delay and periodic interrupt. The counter is updated by the interrupt. The priority of the periodic interrupt is 0.
     * If SW1 is pressed, the counter is incremented by 1; If SW2 is pressed, the counter is decremented by 1. Both SW1 and SW2 generate edge-triggered interrupts to update the counter. The priority of the edge-triggered interrupt is 2.

#### Lab 8 ####
* The system consists of two LaunchPads as shown in Figure 1. Device A and Device B are communicated via the UART1 modules. The UART1 Tx port PB1 on Device A is connected with the UART1 Rx port PB0 on Device B. The ground pins on both devices are also connected.
You need to develop two software projects in this lab, one for each device.
     * Software on Device A: The system is based on the switch_counter_interrupt_TivaWare project. The system has two input switches (SW1 (PF4) and SW2 (PF0)). When either SW1 or SW2 is pressed, a global variable ‘count’ is incremented by 1 using edge-triggered interrupt. Then the updated value of ‘count’ is transmitted to Device B via the UART1 module.
     * Software on Device B: The system receives serial inputs from Device A via the UART1 module. Whenever there is data available on the UART1 Rx pin, a UART1 RX interrupt is generated. In the interrupt service routine, the processor reads the received data from the UART1 module and then sends the data to the TeraTerm terminal via the UART0 module.
