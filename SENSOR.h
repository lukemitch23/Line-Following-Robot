/**********************************************************************************************************************************
*
 *  File name: SENSOR.h
 *  Date: 18/03/2026
 *
 *  Description:
 *
**********************************************************************************************************************************/

#include "COMMON.h"
#include "MOTOR_CONTROL.h"
#include "LIGHT_CONTROL.h"

void SENSOR__Init(void);
void SENSOR__Read_Sensor(void);
void SENSOR__Process_Sensor(void);

bool Check_Reading(void);