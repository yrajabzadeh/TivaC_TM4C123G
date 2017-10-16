#include <stdint.h>
#include <stdbool.h>
#include "lab5.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"

//*****************************************************************************
// Objectives
//
// 1) If SW1 is pressed, then the blue LED will be turned off, and the red LED will be toggled every half second. 
// 2) If SW1 is not pressed, then the red LED will be off, and the blue LED will be toggled every half second. 
//
//
//*****************************************************************************

void
PortFunctionInit(void)
{
    //
    // Enable Peripheral Clocks 
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //
    //
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;
    //
    //Enable pin PF4 for GPIOInput 
    //
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    //
    // Enable pin PF1 for GPIOOutput
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
		//
		// Enable pin PF2 for GPIOOutput
		//
		MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
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

        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0x00) //SW2 is pressed
				{
						// LED OFF
						GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
				}
				else
				{
						// LED ON
						GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
				}
    }
}
