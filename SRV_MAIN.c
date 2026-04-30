/********************************************************************************************************
 *
 * Project: 
 * File name: 
 * File function:
 *
 * Inputs:
 * Outputs:
 *
 * Date: ${{DATE}}
 * Author: Luke Mitchell
 *
********************************************************************************************************/

/* Objects header file */
#include "SRV_MAIN.h"

/***************************************************************************
 * Function name: SRV_MAIN__Timer_Init
 * Purpose: Initialise the timer
 **************************************************************************/

void SRV_MAIN__Timer_Init(void) {
 T0CON0 = 0b10000000; // Set timer to on, 8 bit, and scalar of 1
 T0CON1 = 0b01000110; // Scalar to 1, set synchronous mode
 TMR0L = 0; // clear the timer
 PIR0bits.TMR0IF = 0; // Clear interrupts
 PIE0bits.TMR0IE = 1; // Enable timer
}

/***************************************************************************
 * Function name: SRV_MAIN__Interrupt_Init
 * Purpose: Initialise the timer
 **************************************************************************/
void SRV_MAIN__Interrupt_Init(void) {
 INTCONbits.GIE = 1; // Enable interrupts overall
}