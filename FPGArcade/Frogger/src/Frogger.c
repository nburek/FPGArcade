#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"
#include "frog.h"
#include "enemies.h"
#include "collisions.h"
#include "output_tileset.h"

#define STAGE_MINX 208
#define STAGE_MINY 152
#define STAGE_MAXX 432
#define STAGE_MAXY 328

u32 frogMovementCounter = 0;
#define FROG_MOVEMENT_DELAY 550000
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
	
	drawBackground();
	
	
	u8 joystickLocation = 0;
	u8 frogFrame = 0;
	
	outputCarTiles();
	
	setBackgroundBlock(0,0,raceCarTile1);
	setBackgroundBlock(1,0,raceCarTile2);
	setBackgroundBlock(0,1,raceCarTile3);
	setBackgroundBlock(1,1,raceCarTile4);
	
	setBackgroundBlock(2,0,bullDozerTile1);
	setBackgroundBlock(3,0,bullDozerTile2);
	setBackgroundBlock(2,1,bullDozerTile3);
	setBackgroundBlock(3,1,bullDozerTile4);
	
	setBackgroundBlock(4,0,purpleCarTile1);
	setBackgroundBlock(5,0,purpleCarTile2);
	setBackgroundBlock(4,1,purpleCarTile3);
	setBackgroundBlock(5,1,purpleCarTile4);
	
	setBackgroundBlock(6,0,truckTile1);
	setBackgroundBlock(7,0,truckTile2);
	setBackgroundBlock(8,0,truckTile3);
	setBackgroundBlock(9,0,truckTile4);
	setBackgroundBlock(6,1,truckTile5);
	setBackgroundBlock(7,1,truckTile6);
	setBackgroundBlock(8,1,truckTile7);
	setBackgroundBlock(9,1,truckTile8);
	
	
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
					if(frogger.x + frogger.x_spd < STAGE_MAXX){
						frogger.x += frogger.x_spd;
					}else{
						frogger.x = STAGE_MAXX-8;
					}
					frogger.dir = RIGHT;
					frogFrame = 1-frogFrame;
					break;
				case UP:
					if(frogger.y - frogger.y_spd > STAGE_MINY){
						frogger.y -= frogger.y_spd;
						
					}else{
						frogger.y = STAGE_MINY+8;
					}
					frogger.dir = UP;
					frogFrame = 1-frogFrame;
					break;
				case DOWN:
					if(frogger.y + frogger.y_spd < STAGE_MAXY){
						frogger.y += frogger.y_spd;				
					}else{
						frogger.y = STAGE_MAXY-8;
					}
					frogger.dir = DOWN;
					frogFrame = 1-frogFrame;
					break;
				case LEFT:
					if(frogger.x - frogger.x_spd > STAGE_MINX){
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
