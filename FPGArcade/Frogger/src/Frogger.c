#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"

#define STAGE_MINX 208
#define STAGE_MINY 152
#define STAGE_MAXX 432
#define STAGE_MAXY 328

#define LEFT 3
#define RIGHT 0
#define UP 1
#define DOWN 2

#include "joystickLibrary.h"
#include "graphicsLibrary.h"

#include "frog.h"
#include "enemies.h"
#include "collisions.h"
#include "frog_graphics.h"

void outputFrogger(u8 direction);
void moveFrog();
void DELAY(unsigned time){
	volatile unsigned i;
	for(i = 0; i < time; ++i);
}
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
	
	enableJoystick(&joy1);
	enableJoystick(&joy2);
	
	//do a quick write to initialize positions of objects
	updateJoystick(&joy1, JOYSTICK_1_CHANNEL);
	updateJoystick(&joy2, JOYSTICK_2_CHANNEL);
	
	int i = 0;
	int ii = 0;
	
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(1,i,ii,RED);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(2,i,ii,BLUE);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(3,i,ii,GREEN);
	
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(4,i,ii,WHITE);
			
	for (i = 0; i<8; i=i+2)
		for (ii = 0; ii<8; ++ii)
		{
			setPixel(5,i,ii,WHITE);
			setPixel(5,i+1,ii,RED);
		}
	
	
	/*for (i = 56; i<60; ++i)
		for (ii = 0; ii<80; ++ii)
			setBackgroundBlock(ii,i,3);
	
	for (i = 0; i<56; ++i)
		for (ii = 0; ii<80; ++ii)
			setBackgroundBlock(ii,i,2);*/
			
	for (i = 1; i<80; i = i+2)
		setBackgroundBlock(i,0,5);
		
	for (i = 26; i<54; ++i)
		for (ii = 19; ii<41; ++ii)
			setBackgroundBlock(i,ii,4);
	

	outputFrogger(frogger.dir);
	
	while (1)
	{
		
		DELAY(80000); //1/60ish
		
		
		++frogger.jump_delay;
		if(frogger.jump_delay >= 8){//4 tiles per second
			frogger.jump_delay = 0;
			updateJoystick(&joy1, JOYSTICK_1_CHANNEL);
			
			//no change he won't move
			/* Position Values
			*            5 = deadband
			*            0 = right
			*            1 = top
			*            2 = bottom
			*            3 = left
			*/
			u8 joystickLocation = 0;

			joystickLocation += (joy1.x<joy1.y)?1:0; //if above the first line

			joystickLocation += (joy1.y<1023-joy1.x)?2:0; //if below the second line

			joystickLocation = ((joy1.x-511)*(joy1.x-511) + (joy1.y-511)*(joy1.y-511) < 10000)?5:joystickLocation; //if the joystick is inside the circular deadband

			u8 old_dir = frogger.dir;
			switch(joystickLocation){
			
				case RIGHT:
					if(frogger.x + frogger.x_spd <= STAGE_MAXX){
						frogger.x += frogger.x_spd;
					}else{
						frogger.x = STAGE_MAXX-8;
					}
					frogger.dir = RIGHT;
					break;
				case UP:
					if(frogger.y - frogger.y_spd >= STAGE_MINY){
						frogger.y -= frogger.y_spd;
						
					}else{
						frogger.y = STAGE_MINY+8;
					}
					frogger.dir = UP;
					break;
				case DOWN:
					if(frogger.y + frogger.y_spd <= STAGE_MAXY){
						frogger.y += frogger.y_spd;				
					}else{
						frogger.y = STAGE_MAXY-8;
					}
					frogger.dir = DOWN;
					break;
				case LEFT:
					if(frogger.x - frogger.x_spd >= STAGE_MINX){
						frogger.x -= frogger.x_spd;
					}else{
						frogger.x = STAGE_MINX+8;
					}
					frogger.dir = LEFT;
					break;
				case 5: default: //deadband
					break;
			}
			outputFrogger(frogger.dir);
			//old_dir != frogger.dir?	outputFrogger(frogger.dir):0;
			moveFrog(&frogger);
		}
	
	}

	return XST_SUCCESS;
}
