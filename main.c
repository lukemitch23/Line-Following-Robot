/*=============================================================================================================
*
 * File name: main.c
 * Date: 18/03/2026
 * Author: 24066795
 *
 * Function: Main executive for the LFR. Intialises the ISR and calls all required functions.
 *           Calls all the module initialisation functions and then has an infinite loop creating the
 *           LFR's functions.
=============================================================================================================*/
/* Include required header files */
#include "CONFIGURATION.h"
#include "COMMON.h"
#include "LIGHT_CONTROL.h"
#include "SENSOR.h"
#include "MOTOR_CONTROL.h"

/* Flag to control whether the robot is running */
bool robot_running = false;

/**************************************************************************************************************
 * Function name: Button_Init
 * Purpose: Configures RD3 (start) and RD2 (stop) as digital inputs with internal
 *          pull-ups to prevent floating inputs.
**************************************************************************************************************/
void Button_Init(void){
    /* Set RD3 (start) and RD2 (stop) as inputs */
    TRISDbits.TRISD3 = 1;
    TRISDbits.TRISD2 = 1;
    /* Disable analog on RD3 and RD2 to ensure digital reads */
    ANSELDbits.ANSELD3 = 0;
    ANSELDbits.ANSELD2 = 0;
    /* Enable internal weak pull-ups to prevent floating inputs */
    WPUDbits.WPUD3 = 1;
    WPUDbits.WPUD2 = 1;
}

/**************************************************************************************************************
 * Function name: __interrupt() ISR()
 * Purpose: Interrupt service routine.
**************************************************************************************************************/
void __interrupt() ISR(void){
    /* Reset the timer in case of overflow */
    if (PIR0bits.TMR0IF){
        PIR0bits.TMR0IF = 0;
    }
}

/**************************************************************************************************************
 * Function name: main
 * Purpose: Main function containing executive loop. Calls the initialisation functions and then loops
 *          first reading the line sensor and then acting on its values.
**************************************************************************************************************/
void main(void) {
    /* Call the initisation functions */
    SENSOR__Init();
    LIGHT_CONTROL__Init();
    MOTOR_CONTROL__Init();
    Button_Init();
    /* Main program infinite loop */
    while (1){
        /* Check start button (RD3 pulled low when pressed) */
        if (PORTDbits.RD3 == 0){
            robot_running = true;
            LIGHT_CONTROL__Reverse_Lights(LIGHT_OFF);
            LIGHT_CONTROL__Head_Lights(LIGHT_ON);
        }
        /* Check stop button (RD2 pulled low when pressed) */
        if (PORTDbits.RD2 == 0){
            robot_running = false;
            LIGHT_CONTROL__Reverse_Lights(LIGHT_ON);
            LIGHT_CONTROL__Head_Lights(LIGHT_OFF);
        }
        if (robot_running){
            /* Continously set the PWM duty */
            MOTOR_CONTROL__Set_Duty(30);
            /* Read the sensor and then act on its values */
            SENSOR__Read_Sensor();
            SENSOR__Process_Sensor();
        } else {
            /* Robot is stopped, ensure motors are off */
            MOTOR_CONTROL__Set_Duty(0);
            MOTOR_CONTROL__Stop();
        }
        /* Wait 100ms for stability */
        __delay_ms(100);
    }
}