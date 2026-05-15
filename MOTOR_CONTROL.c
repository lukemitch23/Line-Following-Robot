/*=============================================================================================================
*
 * File name: MOTOR_CONTROL.h
 * Date: 18/03/2026
 * Author: 24066795
 *
 * Function: Handles set and control of the motor function for the LFR. Includes setting up the PWM for the
 *			 correct pins on the MC.
=============================================================================================================*/

/* Include required header files */
#include "COMMON.h"
#include "LIGHT_CONTROL.h"
#include "CONFIGURATION.h"
/* Include the objects header file */
#include "MOTOR_CONTROL.h"




/**************************************************************************************************************
 * Function name: MOTOR_CONTROL__Init()
 * Purpose: Initialise the ports required for motor control and initialise the PWM with the correct
 *			parameters and timers.
**************************************************************************************************************/

void MOTOR_CONTROL__Init(void) {
    /* Disable output drivers on target pins */
    TRISCbits.TRISC3 = 1;
    TRISDbits.TRISD0 = 1;

    /* Ensure pins are digital (not analog) */
    ANSELCbits.ANSELC3 = 0;
    ANSELDbits.ANSELD0 = 0;

    /* Ensure PWM3, PWM4, and Timer2 peripherals are not power-gated */
    PMD3bits.PWM3MD = 0;
    PMD3bits.PWM4MD = 0;

	/* Enable Timer 2 */
    PMD1bits.TMR2MD = 0;

    /* Clear PWM control registers */
    PWM3CON = 0x00;
    PWM4CON = 0x00;

    /* Set PWM period
	* Period = (T2PR + 1) * 4 * Tosc * Prescaler
	* 1ms   = (249 + 1)  * 4 * (1/4MHz) * 4
    * 1ms   = 250 * 1us * 4 = 1000us
	*/
    T2PR = 249;

    /* Set initial duty cycles (50%)
	* 50% of 250 steps = 125. Write to DCH; DCL bits[7:6] = 0
	*/
    PWM3DCH = 125;
    PWM3DCL = 0x00;
    PWM4DCH = 125;
    PWM4DCL = 0x00;

    /* Configure Timer2
	* Clear overflow flag before starting
	*/
    PIR4bits.TMR2IF = 0;

	/* Select the correct clokc source
	* Clock source = FOSC/4 (CS[3:0] = 0001)
	*/
    T2CLKCON = 0x01;

	/* Set prescalar and postscalar
    * CKPS[2:0] = 010 1:4 prescaler
    * OUTPS[3:0] = 0000 1:1 postscaler (postscaler unused for PWM freq)
    * ON = 1 start timer
	*/
    T2CON = 0b10100000;

    /* Wait for first Timer2 overflow to ensure the first PWM output
	* starts as a complete cycle
	*/
    while (!PIR4bits.TMR2IF);

    /* Route PWM outputs to pins via PPS
	* PWM3 Output RD0
	* PWM4 Output RC3
	*/
    RD0PPS = 0x07;
    RC3PPS = 0x08;

    /* Enable output drivers */
    TRISDbits.TRISD0 = 0;
    TRISCbits.TRISC3 = 0;

    /* Enable PWM modules
	* EN=1, OUT=0(read-only), POL=0 (normal)
	*/
    PWM3CON = 0x80;
    PWM4CON = 0x80;

	/* Set up PORT B to be an output, digital and intialise all as off */
	TRISB = 0x00;
    ANSELB = 0x00;
    LATB = 0x00;
}


/**************************************************************************************************************
 * Function name: MOTOR_CONTROL__Forwards()
 * Purpose: Drive the motors forwards and enable the headlights
**************************************************************************************************************/

void MOTOR_CONTROL__Forwards(void) {

 Right_Motor(FORWARD);
 Left_Motor(FORWARD);

 LIGHT_CONTROL__Reverse_Lights(LIGHT_ON);
}

/**************************************************************************************************************
 * Function name: MOTOR_CONTROL__Backwards()
 * Purpose: Reverse the motors
**************************************************************************************************************/

void MOTOR_CONTROL__Backwards() {
 LIGHT_CONTROL__Reverse_Lights(LIGHT_ON);

 Right_Motor(REVERSE);
 Left_Motor(REVERSE);
};

/**************************************************************************************************************
 * Function name: MOTOR_CONTROL__Left()
 * Purpose: Drive the right motor forwards on its own to create a left turn.
 * 			Enable the left indicator light.
**************************************************************************************************************/

void MOTOR_CONTROL__Left(void) {
 LIGHT_CONTROL__Turn_Left(LIGHT_ON);

 Right_Motor(FORWARD);
 Left_Motor(STOP);
}

/**************************************************************************************************************
 * Function name: MOTOR_CONTROL__Right()
 * Purpose: Drive the left motor forwards on its own to create a right turn
 *			Enable the right indicator.
**************************************************************************************************************/

void MOTOR_CONTROL__Right(void) {
 LIGHT_CONTROL__Turn_Right(LIGHT_ON);

 Left_Motor(FORWARD);
 Right_Motor(STOP);
}

/**************************************************************************************************************
 * Function name: MOTOR_CONTROL__Stop()
 * Purpose: Stop both of the motors.
**************************************************************************************************************/

void MOTOR_CONTROL__Stop(void) {
 Right_Motor(STOP);
 Left_Motor(STOP);
 __delay_ms(1000);
}

/**************************************************************************************************************
 * Function name: MOTOR_CONTROL__Set_Duty()
 * Purpose: Set the duty cycle of both of the PWMs by calling their local functions.
**************************************************************************************************************/
void MOTOR_CONTROL__Set_Duty(uint8_t duty){
	PWM3_SetDuty_Percent(duty);
	PWM4_SetDuty_Percent(duty);
}

/**************************************************************************************************************
 * Function name: Left_Motor()
 * Purpose: Branch the input to the function to set the drive direction of the left motor.
**************************************************************************************************************/

void Left_Motor(uint8_t set) {
	switch (set) {
  		case 0:
    		LATBbits.LATB2 = 0;
    		LATBbits.LATB3 = 0;
    		break;
   		case 1:
    		LATBbits.LATB2 = 1;
    		LATBbits.LATB3 = 0;
    		break;
   		case 2:
    		LATBbits.LATB2 = 0;
    		LATBbits.LATB3 = 1;
    		break;
   		default:
    		LATBbits.LATB2 = 0;
    		LATBbits.LATB3 = 0;
   	 		break;
 	}
}

/**************************************************************************************************************
 * Function name: Right_Motor()
 * Purpose: Branch the input to the function to set the drive direction of the right motor.
**************************************************************************************************************/

void Right_Motor(uint8_t set) {
	switch (set) {
  		case 0:
   			LATBbits.LATB0 = 0;
   			LATBbits.LATB4 = 0;
   			break;
  		case 1:
   			LATBbits.LATB0 = 1;
   			LATBbits.LATB4 = 0;
   			break;
  		case 2:
   			LATBbits.LATB0 = 0;
   			LATBbits.LATB4 = 1;
   			break;
  		default:
   			LATBbits.LATB0 = 0;
   			LATBbits.LATB4 = 0;
   			break;
 	}
}

/**************************************************************************************************************
 * Function name: PWM3_SetDuty_Percent()
 * Purpose: Set the PWM3 Duty based off a percentage
**************************************************************************************************************/
void PWM3_SetDuty_Percent(uint8_t percent)
{
	/* Validate our input to be less than 100
	* If greater than 100, set it to be 100
	*/
    if (percent > 100){
		percent = 100;
	}

	/* Convert the percentage into a value for PWM steps
	* Casting the value to a uint16 in order to prevent an overflow
	*/
    uint8_t steps = (uint8_t)((uint16_t)percent * 250 / 100);

	/* Set the value into the higher 8 bits of the PWM duty register
	* No value required in the lower register so set as 0
	*/
    PWM3DCH = steps;
    PWM3DCL = 0x00;
}

/**************************************************************************************************************
 * Function name: PWM4_SetDuty_Percent()
 * Purpose: Set the PWM4 Duty based off a percentage
**************************************************************************************************************/
void PWM4_SetDuty_Percent(uint8_t percent)
{
    /* Validate our input to be less than 100
	* If greater than 100, set it to be 100
	*/
    if (percent > 100){
		percent = 100;
	}

	/* Convert the percentage into a value for PWM steps
	* Casting the value to a uint16 in order to prevent an overflow
	*/
    uint8_t steps = (uint8_t)((uint16_t)percent * 250 / 100);

	/* Set the value into the higher 8 bits of the PWM duty register
	* No value required in the lower register so set as 0
	*/
    PWM4DCH = steps;
    PWM4DCL = 0x00;
}
