/**********************************************************************************************************************************
*
 *  File name: MOTOR_CONTROL.h
 *  Date: 18/03/2026
 *
 *  Description: Header file for the motor control file including the relevent function prototypes.
 *
**********************************************************************************************************************************/

/* Header files */
#include "COMMON.h"
#include "LIGHT_CONTROL.h"

/***************************************************************
 * Function declarations
***************************************************************/

void MOTOR_CONTROL__Init(void);
void MOTOR_CONTROL__Forwards(void);
void MOTOR_CONTROL__Backwards(void);
void MOTOR_CONTROL__Left(void);
void MOTOR_CONTROL__Right(void);
void MOTOR_CONTROL__Stop(void);
void MOTOR_CONTROL__Set_Duty(uint8_t duty);

void Enable_Left(bool set);
void Enable_Right(bool set);
void Left_Motor(uint8_t set);
void Right_Motor(uint8_t set);
void PWM3_SetDuty_Percent(uint8_t percent);
void PWM4_SetDuty_Percent(uint8_t percent);