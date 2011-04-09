#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"
#include "frog.h"
#include "enemies.h"
#include "collisions.h"
#include "frog_graphics.h"

#define STAGE_MINX 208
#define STAGE_MINY 152
#define STAGE_MAXX 432
#define STAGE_MAXY 328


void DELAY(unsigned time){
	volatile unsigned i;
	for(i = 0; i < time; ++i);
}

u32 frogMovementCounter = 0;
#define FROG_MOVEMENT_DELAY 600000
u32 carMovementCounter = 0;




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
	Frog frogger;

	initJoysticks();

	initGraphics();
	
	initFrog(&frogger);
	
	//Do we really need these?
	enableJoystick(&joy1);
	enableJoystick(&joy2);
	
	//I don't think we need to call these here either
	updateJoystick(&joy1, JOYSTICK_1_CHANNEL);
	updateJoystick(&joy2, JOYSTICK_2_CHANNEL);
	
	int i = 0;
	int ii = 0;
	
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(1,i,ii,WHITE);
			
	for (i = 0; i<8; i=i+2)
		for (ii = 0; ii<8; ++ii)
		{
			setPixel(2,i,ii,WHITE);
			setPixel(2,i+1,ii,RED);
		}
			
	for (i = 1; i<80; i = i+2)
		setBackgroundBlock(i,0,2);
		
	for (i = 26; i<54; ++i)
		for (ii = 19; ii<41; ++ii)
			setBackgroundBlock(i,ii,1);
	
	
	
	
	u8 joystickLocation = 0;
	u8 frogFrame = 0;
	
	//start game loop
	while (1)
	{
		++frogMovementCounter;
		++carMovementCounter;
		
		
		if(frogMovementCounter == FROG_MOVEMENT_DELAY)
		{
			frogMovementCounter = 0;
			
			if (frogFrame == 0) //if you're not in the middle of moving already
			{
				//find new joystick location
				updateJoystick(&joy1, JOYSTICK_1_CHANNEL);
				joystickLocation = (joy1.x<joy1.y)?1:0; //if above the first line
				joystickLocation += (joy1.y<1023-joy1.x)?2:0; //if below the second line
				joystickLocation = ((joy1.x-511)*(joy1.x-511) + (joy1.y-511)*(joy1.y-511) < 10000)?5:joystickLocation; //if the joystick is inside the circular deadband
			}

			switch(joystickLocation)
			{
				case RIGHT:
					if(frogger.x + frogger.x_spd <= STAGE_MAXX){
						frogger.x += frogger.x_spd;
					}else{
						frogger.x = STAGE_MAXX-8;
					}
					frogger.dir = RIGHT;
					frogFrame = 1-frogFrame;
					break;
				case UP:
					if(frogger.y - frogger.y_spd >= STAGE_MINY){
						frogger.y -= frogger.y_spd;
						
					}else{
						frogger.y = STAGE_MINY+8;
					}
					frogger.dir = UP;
					frogFrame = 1-frogFrame;
					break;
				case DOWN:
					if(frogger.y + frogger.y_spd <= STAGE_MAXY){
						frogger.y += frogger.y_spd;				
					}else{
						frogger.y = STAGE_MAXY-8;
					}
					frogger.dir = DOWN;
					frogFrame = 1-frogFrame;
					break;
				case LEFT:
					if(frogger.x - frogger.x_spd >= STAGE_MINX){
						frogger.x -= frogger.x_spd;
					}else{
						frogger.x = STAGE_MINX+8;
					}
					frogger.dir = LEFT;
					frogFrame = 1-frogFrame;
					break;
				case 5: default: //deadband
					break;
			}
			
			outputFrogger(frogFrame,frogger.dir,1);
			moveFrog(&frogger);
		} //if(frogMovementCounter == FROG_MOVEMENT_DELAY)
	
	} //end infinite game loop

	return XST_SUCCESS;
}
