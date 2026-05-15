/*=============================================================================================================
*
 * File name: MOTOR_CONTROL.h
 * Date: 18/03/2026
 * Author: 24066795
 *
 * Function: Handles set and control of the motor function for the LFR. Includes setting up the PWM for the
 *			 correct pins on the MC.
=============================================================================================================*/

/**************************************************************************************************************
 *
 * Declare public functions
 *
**************************************************************************************************************/
void MOTOR_CONTROL__Init(void);
void MOTOR_CONTROL__Forwards(void);
void MOTOR_CONTROL__Backwards(void);
void MOTOR_CONTROL__Left(void);
void MOTOR_CONTROL__Right(void);
void MOTOR_CONTROL__Stop(void);
void MOTOR_CONTROL__Set_Duty(uint8_t duty);

/**************************************************************************************************************
 *
 * Declare local functions
 *
**************************************************************************************************************/
void Left_Motor(uint8_t set);
void Right_Motor(uint8_t set);
void PWM3_SetDuty_Percent(uint8_t percent);
void PWM4_SetDuty_Percent(uint8_t percent);