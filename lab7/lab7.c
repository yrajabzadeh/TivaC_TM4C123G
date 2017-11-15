#include <stdint.h>
#include <stdbool.h>
#include "lab7.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"

#define		RED_MASK		0x02
#define		BLUE_MASK		0x04

//*****************************************************************************
//
// The counter increments by 1 every one second.
// If SW1 is pressed, the counter is incremented by 1; If SW2 is pressed, the counter is decremented by 1
//
//*****************************************************************************

// global variable visible in Watch window of debugger
// increments at least once per button press
volatile unsigned long count = 0;

void
PortFunctionInit(void)
{
		//
    // Enable Peripheral Clocks 
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable pin PF4 for GPIOInput
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

    //
    // Enable pin PF0 for GPIOInput
    //
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

    //
    //Open the lock and select the bits modified in the GPIO commit register
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

    //
    //Configuration of the pins that are unlocked
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
		
		GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_1);
		GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2);
		
		//
		//Pull up register for PF4 and PF0
		//
		GPIO_PORTF_PUR_R |= 0x11; 

}
void Timer0A_Init(unsigned long period)
{   
	volatile uint32_t ui32Loop; 
	
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0; // activate timer0
  ui32Loop = SYSCTL_RCGC1_R;				// Do a dummy read to insert a few cycles after enabling the peripheral.
  TIMER0_CTL_R &= ~0x00000001;     // disable timer0A during setup
  TIMER0_CFG_R = 0x00000000;       // configure for 32-bit timer mode
  TIMER0_TAMR_R = 0x00000002;      // configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = period-1;       // reload value
	NVIC_PRI4_R &= ~0xE0000000; 	 // configure Timer0A interrupt priority as 0
  NVIC_EN0_R |= 0x00080000;     // enable interrupt 19 in NVIC (Timer0A)
	TIMER0_IMR_R |= 0x00000001;      // arm timeout interrupt
  TIMER0_CTL_R |= 0x00000001;      // enable timer0A
}

void Timer0A_Handler (void)
{
	TIMER0_ICR_R |= 0x00000001;
	count ++;
}	

//Globally enable interrupts 
void IntGlobalEnable(void)
{
    __asm("    cpsie   i\n");
}


void
Interrupt_Init(void)
{
  NVIC_EN0_R |= 0x40000000;  		// enable interrupt 30 in NVIC (GPIOF)
	NVIC_PRI7_R &= 0x00E00000; 		// configure GPIOF interrupt priority as 0
	GPIO_PORTF_IM_R |= 0x11;   		// arm interrupt on PF0 and PF4
	GPIO_PORTF_IS_R &= ~0x11;     // PF0 and PF4 are edge-sensitive
  GPIO_PORTF_IBE_R |= 0x11;   	// PF0 and PF4 both edges trigger 
  GPIO_PORTF_IEV_R &= ~0x11;  	// PF0 and PF4 falling edge event
	IntGlobalEnable();        		// globally enable interrupt
}

//interrupt handler
void GPIOPortF_Handler(void)
{
	//switch debounce
	NVIC_EN0_R &= ~0x40000000; 
	SysCtlDelay(SysCtlClockGet() / 3);
	NVIC_EN0_R |= 0x40000000; 
	
	//SW1 actions
	if(GPIO_PORTF_RIS_R&0x10)
	{
		// acknowledge flag for PF4
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4); 
		
		//SW1 is pressed	
		//counter imcremented by 1
			count++;
			count=count&3;

	}
	
	//SW2 actions
  if(GPIO_PORTF_RIS_R&0x01)
	{
		// acknowledge flag for PF0
				GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
			
			//SW2 is press
			//counter decremented by 1
			count--;
			count=count&3;
		
	}
	
}

int main(void)
{
	
	unsigned long period = 8000000;
	
	//initialize the GPIO ports	
	PortFunctionInit();
		
	//configure the GPIOF interrupt
	Interrupt_Init();
	
	//initialize Timer0A and configure the interrupt
	Timer0A_Init(period);
	
	//globally enable interrupt
	IntGlobalEnable();
	
    //
    // Loop forever.
    //
    while(1)
    {
			if (count==0)
			{
				GPIO_PORTF_DATA_R &= ~0x06;
			}
			if (count==1)
			{
				GPIO_PORTF_DATA_R &= 0x02;
				GPIO_PORTF_DATA_R ^=RED_MASK;
			}
			if (count==2)
			{
				GPIO_PORTF_DATA_R &= 0x04;
				GPIO_PORTF_DATA_R ^=BLUE_MASK;
			}
			if (count==3)
			{
				GPIO_PORTF_DATA_R &= 0x02;
				GPIO_PORTF_DATA_R ^=RED_MASK;
				GPIO_PORTF_DATA_R &= 0x04;
				GPIO_PORTF_DATA_R ^=BLUE_MASK;
			}
    }
}
