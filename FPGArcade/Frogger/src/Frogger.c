#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"



/*****************************************************************************/
/**
* Main function that starts the frogger game.
*
* @param	None
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful
*
* @note		None
*
******************************************************************************/
int main(void)
{
	u32 Data;
	
	Joystick joy1, joy2;

	initJoysticks();

	initGraphics();
	
	//do a quick write to initialize positions of objects
	getJoystickData(&joy1, JOYSTICK_1_CHANNEL);
	
	getJoystickData(&joy2, JOYSTICK_2_CHANNEL);
	
	setPixel(0,0,0,0xFF);
	setPixel(0,7,7,0X07);
	
	int i = 0;
	int ii = 0;
	
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(0,i,ii,0xFF);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(1,i,ii,0x07);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(2,i,ii,0xC0);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(3,i,ii,0x38);
			
			
	
	setBackgroundBlock(10,10,1);
	setBackgroundBlock(10,9,2);
	setBackgroundBlock(10,8,2);
	setBackgroundBlock(1,1,2);
	
	setMoveableBlock(0,3);
	for (i = 0; i<8; ++i)
		setMoveableBlockRowTransparency(0,i,0x18);
	setMoveableBlockPosition(0,11,11);
	
	setMoveableBlock(15,4);
	setMoveableBlockPosition(15,500,400);
	
	while (1)
	{
		
		
	}

	return XST_SUCCESS;
}


