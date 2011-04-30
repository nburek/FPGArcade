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


/*****************************************************************************/
/**
*
* This function initializes the joystick GPIO device and channels
*
*
* @param		None
*
* @return	None
*
* @note		None
*
****************************************************************************/
void initJoysticks()
{
	XGpio_Initialize(&joystickGPIO, XPAR_JOYSTICK_GPIO_DEVICE_ID);
	XGpio_SetDataDirection(&joystickGPIO, JOYSTICK_1_CHANNEL, 0xFFFFFFFF);
	XGpio_SetDataDirection(&joystickGPIO, JOYSTICK_2_CHANNEL, 0xFFFFFFFF);
}


/*****************************************************************************/
/**
*
* This function reads the data from joystick GPIO device on the channel 
* specified. It then seperates that data out and stores it back into the
* joystick structure that was passed by reference.
*
*
* @param	jstkData is where the joystick data is saved back to
*
* @param	joystickChannel is the channel that is read on the joystick GPIO 
*
* @return	None
*
* @note		None
*
****************************************************************************/
void updateJoystick(Joystick *jstkData, int joystickChannel)
{
	u32 Data;
	u8 Buttons;
	
	Data = XGpio_DiscreteRead(&joystickGPIO, joystickChannel);
	
	(*jstkData).x = (Data & 0x3FF); //read bits 0-9 into X
	
	(*jstkData).y = (Data>>10) & 0x3FF;
	
	(*jstkData).btn1 = (Data >> 21) & 0x1;
	
	(*jstkData).btn2 = (Data >> 22) & 0x1;
	
	(*jstkData).btn3 = (Data >> 20) & 0x1;
	

}


