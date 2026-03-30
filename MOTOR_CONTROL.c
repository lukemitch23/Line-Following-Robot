/**********************************************************************************************************************************
*
 *  File name: MOTOR_CONTROL.c
 *  Date: 18/03/2026
 *
 *  Description:
 *
**********************************************************************************************************************************/

#include <pic18f45k40.h>

#include "MOTOR_CONTROL.h"

void MOTOR_CONTROL__Init() {
 // Set port D to output
 TRISD = 0x00;
 // Set port D to 0
 LATD = 0x00;
}

void MOTOR_CONTROL__Forwards() {
 LATDbits.LATD0 = 1;
 LATDbits.LATD1 = 0;
 LATDbits.LATD2 = 1;
 LATDbits.LATD3 = 0;
};

void MOTOR_CONTROL__Backwards() {
 LATDbits.LATD0 = 0;
 LATDbits.LATD1 = 1;
 LATDbits.LATD2 = 0;
 LATDbits.LATD3 = 1;
};
