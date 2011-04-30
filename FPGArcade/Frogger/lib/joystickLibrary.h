#ifndef JOYSTK_LIB_H
#define JOYSTK_LIB_H

#include "xparameters.h"
#include "xgpio.h"

#define JOYSTICK_1_CHANNEL 1
#define JOYSTICK_2_CHANNEL 2

typedef struct joystick_struct{

	// will have a value between 0 and 1023
	u16 x;
	u16 y;

	u8 btn1;
	u8 btn2;
	u8 btn3;
	
	
}Joystick;

XGpio joystickGPIO;


#endif

