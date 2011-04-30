#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"
#include "frog.h"
#include "enemies.h"
#include "collisions.h"
#include "output_tileset.h"

//the limits for the frogger game stage
#define STAGE_MINX 208
#define STAGE_MINY 152
#define STAGE_MAXX 432
#define STAGE_MAXY 328

//where the water starts at
#define WATER_LINE 240

//the variables and constants used for timing
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
u32 log1MovementCounter = 28000;
#define LOG1_MOVEMENT_DELAY 40000
u32 log2MovementCounter = 28000;
#define LOG2_MOVEMENT_DELAY 60000
u32 collisionDetectionCounter = 500;
#define COLLISION_DETECTION_DELAY 10000

//Begin Function Prototypes
void writeHiScore(u32 score);
void writeScore(u32 score);

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
	
	u32 highScore = 1000; //the high score
	
	initJoysticks(); //initialize joystick communication

	initGraphics(); //initialize graphics communication
		
	while(1) //program loop
	{ 
		u8 cCheck = 0; //used with collision detection
		u32 currentScore = 0; //the current games score
		s8 highestLane = -1; //the highest lane you've reached this life
		u8 joystickLocation = 0; //which direction you're pressing the joystick
		u8 frogFrame = 0; //which animation frame of the frog should be shown
		
		Joystick joy1; //the joystick interface
		Frog frogger; //the data for the frog
		
		initFrog(&frogger); 
		
		drawBackground(); //ouput tiles needed for background and other graphics
		
		outputCarTiles(); //outputs all the car tiles
		
		initMovingObjects(); //initialize the position of all the moving objects
		
		drawLives(frogger.lives);
		
		//draw the scores
		writeScore(currentScore);
		writeHiScore(highScore);
		
		while (frogger.lives > 0 ) //game loop
		{
			//begin timer incrementing
			++frogMovementCounter;
			++raceCarMovementCounter;
			++truckMovementCounter;
			++bullDozerMovementCounter;
			++purpleCarMovementCounter;
			++turtleMovementCounter;
			++log1MovementCounter;
			++log2MovementCounter;
			++collisionDetectionCounter;
			
			//find which lane the frog is in
			s16 froggerBY = (frogger.y -8) /8;
			s16 lane = (FIRST_ROW_Y - froggerBY) /2;
			
			if (lane > highestLane) //check for forward movement
			{
				highestLane = lane;
				currentScore += 10;
				writeScore(currentScore);
			}
			
			// collision detection event
			if (collisionDetectionCounter >= COLLISION_DETECTION_DELAY)
			{
				collisionDetectionCounter = 0;
				
				//if you're in a lane with moving objects
				if(lane >= 0 && lane <= 9 && lane!=4)
				{
					if (lane == 9) //if you're in the final row
					{
						highestLane = -1;
						if(frogger.x%48 == 32) //if you made it into one of the slots
						{
							//reached end, so add to score and reset
							currentScore += 200;
							writeScore(currentScore);
							
							//do a flashing animation
							int i,ii ;
							for (i = 0; i<4; ++i)
								for (ii = 0; ii<300; ++ii)
									outputFrogger(i%2,frogger.dir,2);
							
							//reset the frog's position
							frogger.x = 320;
							frogger.y = 320;
							outputFrogger(0,frogger.dir,1);
							moveFrog(&frogger);
						}
						else //kill the frog
						{
							dieFrog(&frogger);
							frogFrame = 0;
							drawLives(frogger.lives);
						}
					}
					else
					{
						//check for collision with objects in the current row
						cCheck = checkCollision(movingObjectsX[lane], movingObjectsWidth[lane], frogger.x);
						
						//if you're in the water and not on top of something or you're hit by a car
						if((cCheck && frogger.y>WATER_LINE) || (!cCheck && frogger.y<=WATER_LINE && frogFrame==0))
						{
							dieFrog(&frogger);
							frogFrame = 0;
							drawLives(frogger.lives);
							highestLane = -1;
						}
					}
				}
				else
				{
					cCheck = 0;
				}
			}
			
			//frog movement event
			if(frogMovementCounter > FROG_MOVEMENT_DELAY)
			{
				frogMovementCounter = 0;
				
				if (frogFrame == 0) //if you're not in the middle of moving already
				{
					//find new joystick location
					updateJoystick(&joy1, JOYSTICK_1_CHANNEL);
					joystickLocation = (joy1.x<joy1.y)?1:0; //if above the first diagonal line
					joystickLocation += (joy1.y<1023-joy1.x)?2:0; //if below the second diagonal line
					joystickLocation = ((joy1.x-511)*(joy1.x-511) + (joy1.y-511)*(joy1.y-511) < 10000)?5:joystickLocation; //if the joystick is inside the circular deadband
				}

				//handle the joystick input
				switch(joystickLocation)
				{
					case RIGHT:
						//move right if you aren't at the edge of the screen
						if(frogger.x + frogger.x_spd < STAGE_MAXX)
						{
							frogger.x += frogger.x_spd;
						}
						else
						{
							frogger.x = STAGE_MAXX-8;
						}
						frogger.dir = RIGHT; //set which direction the frog is facing
						frogFrame = 1-frogFrame; //change the animation frame
						break;
					case UP:
						//move up if you aren't at the edge of the screen
						if(frogger.y - frogger.y_spd > STAGE_MINY){
							frogger.y -= frogger.y_spd;
						}else{
							frogger.y = STAGE_MINY+8;
						}
						frogger.dir = UP;
						frogFrame = 1-frogFrame;
						break;
					case DOWN:
						//move down if you aren't at the edge of the screen
						if(frogger.y + frogger.y_spd < STAGE_MAXY){
							frogger.y += frogger.y_spd;				
						}else{
							frogger.y = STAGE_MAXY-8;
						}
						frogger.dir = DOWN;
						frogFrame = 1-frogFrame;
						break;
					case LEFT:
						//move left if you aren't at the edge of the screen
						if(frogger.x - frogger.x_spd > STAGE_MINX){
							frogger.x -= frogger.x_spd;
						}else{
							frogger.x = STAGE_MINX+8;
						}
						frogger.dir = LEFT;
						frogFrame = 1-frogFrame;
						break;
					case 5: default: //deadband
						//don't do anything
						break;
				}
				
				outputFrogger(frogFrame,frogger.dir,1);
				moveFrog(&frogger);
			} //if(frogMovementCounter == FROG_MOVEMENT_DELAY)
		
			//race car movement event
			if (raceCarMovementCounter > RACE_CAR_MOVEMENT_DELAY)
			{
				raceCarMovementCounter = 0;
				moveRow(Race_Car);
			}
			
			//truck movement event
			if (truckMovementCounter > TRUCK_MOVEMENT_DELAY)
			{
				truckMovementCounter = 0;
				moveRow(Truck);
			}
			
			//bull dozer movement event
			if (bullDozerMovementCounter > BULL_DOZER_MOVEMENT_DELAY)
			{
				bullDozerMovementCounter = 0;
				moveRow(Bull_Dozer);
			}
			
			//purple car movement event
			if (purpleCarMovementCounter > PURPLE_CAR_MOVEMENT_DELAY)
			{
				purpleCarMovementCounter = 0;
				moveRow(Purple_Car);
			}
			
			//turtle movement event
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
			
			//first lane of logs movement event
			if (log1MovementCounter > LOG1_MOVEMENT_DELAY)
			{
				if (lane == 6  && (frogFrame==0) && (frogger.x+8)<STAGE_MAXX)
				{
					frogger.x += 8;
					moveFrog(&frogger);
				}
				log1MovementCounter = 0;
				moveRow(Log);
			}
			
			//second lane of logs movement event
			if (log2MovementCounter > LOG2_MOVEMENT_DELAY)
			{
				if (lane == 8 && (frogFrame==0) && (frogger.x+8)<STAGE_MAXX)
				{
					frogger.x += 8;
					moveFrog(&frogger);
				}
				log2MovementCounter = 0;
				moveRow(Log2);
			}
			
		} //end game loop
		
		clearFrog(&frogger);
		//fill screen with x's
		int i, j;
		for (i = 25; i<55; ++i){
			for (j = 17; j<42; ++j){
				setBackgroundBlock(i,j,27);
			}
		}
		
		//check for new high score
		if (currentScore>highScore)
		{
			highScore = currentScore;
			writeHiScore(highScore);
		}
		
		currentScore = 0; //reset current game score
		
		//wait for button 1 to be pressed on the joystick
		while(joy1.btn1 != 1){
			updateJoystick(&joy1, JOYSTICK_1_CHANNEL);
		}
	
	} // end program loop
	

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* Displays the score on the screen in the high score spot.
*
*
* @param		u32 score - the value you want to display
*
* @return	None
*
* @note		None
*
****************************************************************************/
void writeHiScore(u32 score){

	u32 temp = score;
	
	u32 i = 0;
	do {
		u32 digit = temp%10;
		temp /= 10;
		
		setBackgroundBlock(54 - i,15,digit);
		
		++i;
	} while(temp != 0);

}

/*****************************************************************************/
/**
*
* Displays the score on the screen in the current score spot.
*
*
* @param		u32 score - the value you want to display
*
* @return	None
*
* @note		None
*
****************************************************************************/
void writeScore(u32 score)
{
	u32 temp = score;
	
	u32 i;
	for (i = 40; i<80; ++i)
		setBackgroundBlock(i,16,10);
	
	i = 0;
	do {
		u32 digit = temp%10;
		temp /= 10;
		
		setBackgroundBlock(54 - i,16,digit);
		
		++i;
	} while(temp != 0);
}
