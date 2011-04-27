#define RESX 640
#define RESY 480

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

#define WATER_LINE 240

u32 frogMovementCounter = 10000;
#define FROG_MOVEMENT_DELAY 50000
u32 raceCarMovementCounter = 5000;
#define RACE_CAR_MOVEMENT_DELAY 50000
u32 truckMovementCounter = 0;
#define TRUCK_MOVEMENT_DELAY 80000
u32 bullDozerMovementCounter = 14000;
#define BULL_DOZER_MOVEMENT_DELAY 60000
u32 purpleCarMovementCounter = 20000;
#define PURPLE_CAR_MOVEMENT_DELAY 40000
u32 turtleMovementCounter = 17000;
#define TURTLE_MOVEMENT_DELAY 40000
u32 logMovementCounter = 28000;
#define LOG_MOVEMENT_DELAY 60000
u32 collisionDetectionCounter = 500;
#define COLLISION_DETECTION_DELAY 10000


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
	
	Joystick joy1;
	Frog frogger;

	initJoysticks();

	initGraphics();
	
	initFrog(&frogger);
	
	drawBackground();
	
	
	u8 joystickLocation = 0;
	u8 frogFrame = 0;
	
	outputCarTiles();
	
	initMovingObjects();
	
	drawLives(frogger.lives);
	
	//u8 branchExecuted;
	
	u8 win = 0;
	u8 cCheck = 0;
	//start game loop
	while (1)
	{
	
		if(frogger.lives <= 0 || win == 1){
			break;
		}
		
		++frogMovementCounter;
		++raceCarMovementCounter;
		++truckMovementCounter;
		++bullDozerMovementCounter;
		++purpleCarMovementCounter;
		++turtleMovementCounter;
		++logMovementCounter;
		++collisionDetectionCounter;
		
		//u16 froggerBX = (frogger.x -8) /8;
		s16 froggerBY = (frogger.y -8) /8;
		s16 lane = (FIRST_ROW_Y - froggerBY) /2;
		
		if (collisionDetectionCounter >= COLLISION_DETECTION_DELAY)
		{
			collisionDetectionCounter = 0;
			if(lane >= 0 && lane <= 9 && lane!=4)
			{
				if (lane == 9)
				{
					if(frogger.x%48 == 32)
						win = 1;
					else
					{
						dieFrog(&frogger);
						frogFrame = 0;
						drawLives(frogger.lives);
					}
				}
				else
				{
					cCheck = checkCollision(movingObjectsX[lane], movingObjectsWidth[lane], frogger.x);
					if((cCheck && frogger.y>WATER_LINE) || (!cCheck && frogger.y<=WATER_LINE && frogFrame==0))
					{
						dieFrog(&frogger);
						frogFrame = 0;
						drawLives(frogger.lives);
					}
				}
			}
			else
			{
				cCheck = 0;
			}
		}
		if(frogMovementCounter > FROG_MOVEMENT_DELAY)
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
					if(frogger.x + frogger.x_spd < STAGE_MAXX)
					{
						frogger.x += frogger.x_spd;
					}
					else
					{
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
	
	
		if (raceCarMovementCounter > RACE_CAR_MOVEMENT_DELAY)
		{
			raceCarMovementCounter = 0;
			moveRow(Race_Car);
		}
		
		if (truckMovementCounter > TRUCK_MOVEMENT_DELAY)
		{
			truckMovementCounter = 0;
			moveRow(Truck);
		}
		
		if (bullDozerMovementCounter > BULL_DOZER_MOVEMENT_DELAY)
		{
			bullDozerMovementCounter = 0;
			moveRow(Bull_Dozer);
		}
		
		if (purpleCarMovementCounter > PURPLE_CAR_MOVEMENT_DELAY)
		{
			purpleCarMovementCounter = 0;
			moveRow(Purple_Car);
		}
		
		if (turtleMovementCounter > TURTLE_MOVEMENT_DELAY)
		{
			if ((lane == 5 || lane == 7) && (frogFrame==0) && (frogger.x-8)>STAGE_MINX)
			{
				frogger.x -= 8;
				moveFrog(&frogger);
			}
			turtleMovementCounter = 0;
			moveRow(Turtle);
			moveRow(Turtle2);
		}
		
		if (logMovementCounter > LOG_MOVEMENT_DELAY)
		{
			if ((lane == 6 || lane == 8) && (frogFrame==0) && (frogger.x+8)<STAGE_MAXX)
			{
				frogger.x += 8;
				moveFrog(&frogger);
			}
			logMovementCounter = 0;
			moveRow(Log);
			moveRow(Log2);
		}
		
		/*while (branchExecuted>0)
		{
			frogMovementCounter+=100;
			raceCarMovementCounter+=100;
			truckMovementCounter+=100;
			bullDozerMovementCounter+=100;
			purpleCarMovementCounter+=100;
			turtleMovementCounter+=100;
			logMovementCounter+=100;
			--branchExecuted;
		}*/
		
	} //end infinite game loop
	
	//fill screen with x's
	
	int i, j;
	for (i = 25; i<55; ++i){
		for (j = 17; j<42; ++j){

			if(win == 1){
				setBackgroundBlock(i,j,29);
			}else{
				setBackgroundBlock(i,j,27);
			}
		}
	}

	return XST_SUCCESS;
}
