#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

#define 	RED_MASK 		0x02
//*****************************************************************************
//
// RED LED stays on until SW2 is pushed
//
//*****************************************************************************


void
PortFunctionInit(void)
{

		volatile uint32_t ui32Loop;   
	
		// Enable the clock of the GPIO port that is used for the on-board LED and switch.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ui32Loop = SYSCTL_RCGC2_R;

		// Unlock GPIO Port F
		GPIO_PORTF_LOCK_R = 0x4C4F434B;   
		
		// allow changes to PF0
		GPIO_PORTF_CR_R |= 0x01;  

    // Set the direction of PF2 (RED LED) as output
    GPIO_PORTF_DIR_R |= 0x02;
	
		// Set the direction of PF0 (SW2) as input by clearing the bit
    GPIO_PORTF_DIR_R &= ~0x01;
	
    // Enable both PF2 and PF0 for digital function.
    GPIO_PORTF_DEN_R |= 0x03;
	
		//Enable pull-up on PF0
		GPIO_PORTF_PUR_R |= 0x01; 

}


int main(void)
{
	
		//initialize the GPIO ports	
		PortFunctionInit();
	
    //
    // Loop forever.
    //
    while(1)
    {

        if((GPIO_PORTF_DATA_R&0x01)==0x00) //SW2 is pressed
				{
						// LED OFF
						GPIO_PORTF_DATA_R &= ~0x02;
				}
				else
				{
						// LED ON
						GPIO_PORTF_DATA_R |= 0x02;
				}
    }
}
