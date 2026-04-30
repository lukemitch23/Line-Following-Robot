/**********************************************************************************************************************************
*
 *  File name: SENSOR.c
 *  Date: 18/03/2026
 *
 *  Description:
 *
**********************************************************************************************************************************/

#include "SENSOR.h"


bool Sensor_Value_g[5] = {0,0,0,0,0};

void SENSOR__Init(void) {
    // ANSEL ? whole-register writes are fine here since 0 = digital on all pins,
    // which is correct for the PWM pins too
    ANSELD = 0;
    ANSELC = 0;

	TRISDbits.TRISD7 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD4 = 1;

	TRISCbits.TRISC7 = 1;
}

void SENSOR__Read_Sensor(void) {
 for (int index = 0; index < 5; index++) {
  switch (index) {
   case 0:
     Sensor_Value_g[index] = !RD7;
     break;
   case 1:
    Sensor_Value_g[index] = !PORTDbits.RD6;
    break;
   case 2:
    Sensor_Value_g[index] = !PORTDbits.RD5;
    break;
   case 3:
    Sensor_Value_g[index] = !PORTDbits.RD4;
    break;
   case 4:
    Sensor_Value_g[index] = !PORTCbits.RC7;
    break;
   default:
    Sensor_Value_g[index] = 0;
  }
 }
}

void SENSOR__Process_Sensor(void) {
/*
 if (Sensor_Value_g[2]) {
  //LIGHT_CONTROL__Turn_Left(0);
  //LIGHT_CONTROL__Turn_Right(0);
  MOTOR_CONTROL__Forwards();
 } else if (Sensor_Value_g[1] || Sensor_Value_g[0]) {
  MOTOR_CONTROL__Left();
 } else if (Sensor_Value_g[3] || Sensor_Value_g[4]) {
  MOTOR_CONTROL__Right();
 } else if (!Sensor_Value_g[0] && !Sensor_Value_g[1] && !Sensor_Value_g[2] && !Sensor_Value_g[3] && !Sensor_Value_g[4]) {
  MOTOR_CONTROL__Stop();
 }
*/
	if (Sensor_Value_g[2]) {
		LIGHT_CONTROL__Head_Lights(1);
		LIGHT_CONTROL__Reverse_Lights(0);
        MOTOR_CONTROL__Forwards();
	} else {
		LIGHT_CONTROL__Head_Lights(0);
		MOTOR_CONTROL__Stop();
	}

	if (Sensor_Value_g[3] || Sensor_Value_g[4]) {
		LIGHT_CONTROL__Turn_Left(1);
		MOTOR_CONTROL__Left();
	}

	if (Sensor_Value_g[1] || Sensor_Value_g[0]) {
		LIGHT_CONTROL__Turn_Right(1);
		MOTOR_CONTROL__Right();
	}

	if (!Sensor_Value_g[0] && !Sensor_Value_g[1] && !Sensor_Value_g[2] && !Sensor_Value_g[3] && !Sensor_Value_g[4]){
		LIGHT_CONTROL__Reverse_Lights(1);
		MOTOR_CONTROL__Stop();
	}
}

