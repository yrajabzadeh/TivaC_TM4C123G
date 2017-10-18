#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"

#define		RED_MASK		0x02
#define		BLUE_MASK		0x04

//*****************************************************************************
// Objectives
//
// 1) If SW1 is pressed, then the blue LED will be turned off, and the red LED will be toggled every half second. 
// 2) If SW1 is not pressed, then the red LED will be off, and the blue LED will be toggled every half second. 
//
//*****************************************************************************

void
PortFunctionInit(void)
{
//
		volatile uint32_t ui32Loop;   
	// Enable the GPIO port that is used for the on-board LED.
    //
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ui32Loop = SYSCTL_RCGC2_R;
	
		// Unlock GPIO Port F
		GPIO_PORTF_LOCK_R = 0x4C4F434B;   
		
		// allow changes to PF0
		GPIO_PORTF_CR_R |= 0x01;

		// Set the direction of PF2 (BLUE LED) as output
    GPIO_PORTF_DIR_R |= 0x04;
	
		// Set the direction of PF0 (SW2) as input by clearing the bit
    GPIO_PORTF_DIR_R &= ~0x01;
	
    // Enable both PF2 and PF0 for digital function.
    GPIO_PORTF_DEN_R |= 0x03;
	
		//Enable pull-up on PF0
		GPIO_PORTF_PUR_R |= 0x01;

    //
    // Enable the GPIO pin for the BLUE LED (PF2) and RED LED (PF 1)
    //
		
    GPIO_PORTF_DIR_R |= 0x04;
    GPIO_PORTF_DEN_R |= 0x04;
		
		GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;

}


int main(void)
{
	
		//initialize the GPIO ports	
		PortFunctionInit();
    //
    // while loop
    //
    while(1)
    {
			if ((GPIO_PORTF_DATA_R&0x01)==0x00)// SW2 is pressed
			{
				GPIO_PORTF_DATA_R &= 0x02;
        // Delay
				//sets number of cycles
				SysCtlDelay(900000);	
        // Toggle the LED.
        GPIO_PORTF_DATA_R ^=RED_MASK;
			}
			else
			{
				GPIO_PORTF_DATA_R &= 0x04;
        // Delay
				//sets number of cycles
				SysCtlDelay(900000);	
        // Toggle the LED.
        GPIO_PORTF_DATA_R ^=BLUE_MASK;
			}
    }
}
