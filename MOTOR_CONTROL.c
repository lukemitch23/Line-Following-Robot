/**********************************************************************************************************************************
*
 *  File name: MOTOR_CONTROL.c
 *  Date: 18/03/2026
 *
 *  Description:
 *
**********************************************************************************************************************************/

/* Objects header file */
#include "MOTOR_CONTROL.h"

/***************************************************************************
 * Function name: MOTOR_CONTROL__Init()
 * Purpose: Initialise ports for the motor
 **************************************************************************/

void MOTOR_CONTROL__Init(void) {
    // --- Step 1: Disable output drivers on target pins ---
    TRISCbits.TRISC3 = 1;
    TRISDbits.TRISD0 = 1;

    // --- Ensure pins are digital (not analog) ---
    ANSELCbits.ANSELC3 = 0;
    ANSELDbits.ANSELD0 = 0;

    // --- Ensure PWM3, PWM4, and Timer2 peripherals are not power-gated ---
    PMD3bits.PWM3MD = 0;
    PMD3bits.PWM4MD = 0;
    PMD1bits.TMR2MD = 0;   // Enable Timer2

    // --- Step 2: Clear PWM control registers ---
    PWM3CON = 0x00;
    PWM4CON = 0x00;

    // --- Step 3: Set PWM period ---
    // Period = (T2PR + 1) * 4 * Tosc * Prescaler
    // 1ms   = (249 + 1)  * 4 * (1/4MHz) * 4
    // 1ms   = 250 * 1us * 4 = 1000us ?
    T2PR = 249;

    // --- Step 4: Set initial duty cycles (50%) ---
    // 50% of 250 steps = 125. Write to DCH; DCL bits[7:6] = 0
    PWM3DCH = 125;
    PWM3DCL = 0x00;
    PWM4DCH = 125;
    PWM4DCL = 0x00;

    // --- Step 5: Configure Timer2 ---
    PIR4bits.TMR2IF = 0;    // Clear overflow flag before starting

    T2CLKCON = 0x01;        // Clock source = FOSC/4 (CS[3:0] = 0001)
                            // Required for correct PWM operation

    // CKPS[2:0] = 010 ? 1:4 prescaler
    // OUTPS[3:0] = 0000 ? 1:1 postscaler (postscaler unused for PWM freq)
    // ON = 1 ? start timer
    T2CON = 0b10100000;     // ON=1, CKPS=010, OUTPS=0000

    // --- Step 6: Wait for first Timer2 overflow ---
    // Ensures the first PWM output starts as a complete cycle
    while (!PIR4bits.TMR2IF);

    // --- Step 7: Route PWM outputs to pins via PPS ---
    RD0PPS = 0x07;          // PWM3 output ? RD0
    RC3PPS = 0x08;          // PWM4 output ? RC3

    // Enable output drivers
    TRISDbits.TRISD0 = 0;
    TRISCbits.TRISC3 = 0;

    // --- Step 8: Enable PWM modules ---
    PWM3CON = 0x80;         // EN=1, OUT=0(read-only), POL=0 (normal)
    PWM4CON = 0x80;
}


/***************************************************************************
 * Function name: MOTOR_CONTROL__Forwards()
 * Purpose: Drive motors forwards
 ***************************************************************************/

void MOTOR_CONTROL__Forwards(void) {

 Right_Motor(FORWARD);
 Left_Motor(FORWARD);

 LIGHT_CONTROL__Reverse_Lights(LIGHT_ON);
}

/***************************************************************************
 * Function name: MOTOR_CONTROL__Backwards()
 * Purpose: Drive motors backwards
 **************************************************************************/

void MOTOR_CONTROL__Backwards() {
 LIGHT_CONTROL__Reverse_Lights(LIGHT_ON);
 Enable_Left(MOTOR_ON);
 Enable_Right(MOTOR_ON);
 Right_Motor(REVERSE);
 Left_Motor(REVERSE);
};

/***************************************************************************
 * Function name: MOTOR_CONTROL__Left()
 * Purpose: Turn left
 **************************************************************************/

void MOTOR_CONTROL__Left(void) {
 LIGHT_CONTROL__Turn_Left(LIGHT_ON);
 Enable_Left(MOTOR_OFF);
 Enable_Right(MOTOR_ON);
 Right_Motor(FORWARD);
 Left_Motor(STOP);
}

/***************************************************************************
 * Function name: MOTOR_CONTROL__Right()
 * Purpose: Turn right
 **************************************************************************/

void MOTOR_CONTROL__Right(void) {
 LIGHT_CONTROL__Turn_Right(LIGHT_ON);
 Enable_Left(MOTOR_ON);
 Enable_Right(MOTOR_OFF);
 Left_Motor(FORWARD);
 Right_Motor(STOP);
}

/***************************************************************************
 * Function name: MOTOR_CONTROL__Stop()
 * Purpose: Stop motors
 **************************************************************************/

void MOTOR_CONTROL__Stop(void) {
 Right_Motor(STOP);
 Left_Motor(STOP);
}

/***************************************************************************
 * Function name: MOTOR_CONTROL__Set_Duty(uint8_t duty)
 * Purpose: Set the duty percentage for both
 **************************************************************************/
void MOTOR_CONTROL__Set_Duty(uint8_t duty){
	PWM3_SetDuty_Percent(duty);
	PWM4_SetDuty_Percent(duty);
}

/***************************************************************************
 * Function name: Enable_Left
 * Purpose: Control the left motor enable pin
 **************************************************************************/

void Enable_Left(bool set) {

}

/***************************************************************************
 * Function name: Enable_Right
 * Purpose: Control the right motor enable pin
 **************************************************************************/

void Enable_Right(bool set) {

}
/***************************************************************************
 * Function name: Left_Motor
 * Purpose: Drive the correct pins high to chose the motors spin direction
 **************************************************************************/

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

/***************************************************************************
 * Function name: Right_Motor
 * Purpose: Drive the correct pins high to chose the motors spin direction
 **************************************************************************/

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

/***************************************************************************
 * Function name: PWM3_Set_Duty
 * Purpose: Set the PWM3 Duty
 **************************************************************************/
void PWM3_SetDuty_Percent(uint8_t percent)
{
    if (percent > 100) percent = 100;
    uint8_t steps = (uint8_t)((uint16_t)percent * 250 / 100);
    PWM3DCH = steps;
    PWM3DCL = 0x00;
}

/***************************************************************************
 * Function name: PWM4_Set_Duty
 * Purpose: Set the PWM4 Duty
 **************************************************************************/
void PWM4_SetDuty_Percent(uint8_t percent)
{
    if (percent > 100) percent = 100;
    uint8_t steps = (uint8_t)((uint16_t)percent * 250 / 100);
    PWM4DCH = steps;
    PWM4DCL = 0x00;
}
