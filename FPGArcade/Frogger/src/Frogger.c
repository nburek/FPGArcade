#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"


void outputFrogger(int direction);
void moveFrog(int x, int y);

#define FROG_TILE_1 60
#define FROG_TILE_2 61
#define FROG_TILE_3 62
#define FROG_TILE_4 63

#define FROG_BLOCK_1 0
#define FROG_BLOCK_2 1
#define FROG_BLOCK_3 2
#define FROG_BLOCK_4 3


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
	
	int i = 0;
	int ii = 0;
	
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(0,i,ii,WHITE);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(1,i,ii,RED);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(2,i,ii,BLUE);
			
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(3,i,ii,GREEN);
	
	for (i = 0; i<8; i=i+2)
		for (ii = 0; ii<8; ++ii)
		{
			setPixel(4,i,ii,WHITE);
			setPixel(4,i+1,ii,RED);
		}
	
	setMoveableBlock(5,4);
	setMoveableBlockPosition(5,0,400);
	
	setBackgroundBlock(10,10,1);
	setBackgroundBlock(10,9,2);
	setBackgroundBlock(10,8,2);
	setBackgroundBlock(1,1,2);
	
	for (i = 56; i<60; ++i)
		for (ii = 0; ii<80; ++ii)
			setBackgroundBlock(ii,i,3);
	
	for (i = 0; i<56; ++i)
		for (ii = 0; ii<80; ++ii)
			setBackgroundBlock(ii,i,2);
			
	for (i = 1; i<80; i = i+2)
		setBackgroundBlock(i,1,4);
	
	setBackgroundBlock(40,40,60);
	setBackgroundBlock(42,42,61);
	setBackgroundBlock(44,44,62);
	setBackgroundBlock(46,46,63);
	/*
	setMoveableBlock(0,1);
	setMoveableBlockRowTransparency(0,0,0xE7);
	setMoveableBlockRowTransparency(0,1,0xC3);
	setMoveableBlockRowTransparency(0,2,0x81);
	setMoveableBlockRowTransparency(0,3,0x00);
	setMoveableBlockRowTransparency(0,4,0x00);
	setMoveableBlockRowTransparency(0,5,0x81);
	setMoveableBlockRowTransparency(0,6,0xC3);
	setMoveableBlockRowTransparency(0,7,0xE7);
	setMoveableBlockPosition(0,11,11);
	*/
	//setMoveableBlock(15,4);
	//setMoveableBlockPosition(15,500,400);

	outputFrogger(0);
//	moveFrog(49,79);
	setMoveableBlockPosition(FROG_BLOCK_1,2,24);
	
	setPixel(5,0,0,WHITE);
	setPixel(5,0,2,RED);
	setPixel(5,0,4,BLUE);
	setPixel(5,0,6,GREEN);
	setPixel(5,1,7,WHITE);
	setPixel(5,3,7,WHITE);
	setPixel(5,5,7,WHITE);
	setPixel(5,7,7,WHITE);
	setMoveableBlock(8,5);
	setMoveableBlockPosition(8,0,2);
	
	while (1)
	{
		
		
	}

	return XST_SUCCESS;
}


/*
	Directions: 0 - up, 1 - right, 2 - down, 3 - left
*/
void outputFrogger(int direction)
{

	u8 colors[] = {RED, GREEN, BLUE, WHITE, BLACK, YELLOW, PURPLE};
	int arrayX, arrayY, tileX, tileY;
	
	setMoveableBlock(FROG_BLOCK_1, FROG_TILE_1);
	setMoveableBlock(FROG_BLOCK_2, FROG_TILE_2);
	setMoveableBlock(FROG_BLOCK_3, FROG_TILE_3);
	setMoveableBlock(FROG_BLOCK_4, FROG_TILE_4);
	
	u8 frog1[8][8] = {{4,4,4,4,4,4,4,4},
							{4,4,4,4,4,4,4,4},
							{4,4,4,1,4,4,4,4},
							{4,4,1,1,4,4,5,1},
							{4,4,4,1,4,6,1,5},
							{4,4,4,1,4,1,1,5},
							{4,4,4,4,1,5,5,5},
							{4,4,4,4,4,5,1,5}};
	u8 frog2[8][8] = {{4,4,4,4,4,4,4,4},
							{4,4,4,4,4,4,4,4},
							{4,4,4,4,1,4,4,4},
							{5,5,4,4,1,1,4,4},
							{5,1,6,4,1,4,4,4},
							{5,1,1,4,1,4,4,4},
							{5,5,5,1,4,4,4,4},
							{5,5,5,4,4,4,4,4}};
	u8 frog3[8][8] = {{4,4,4,4,4,5,1,5},
							{4,4,4,4,4,1,5,1},
							{4,4,4,4,1,1,1,5},
							{4,4,4,1,1,4,4,4},
							{4,4,4,1,4,4,4,4},
							{4,4,1,1,4,4,4,4},
							{4,4,4,1,4,4,4,4},
							{4,4,4,4,4,4,4,4}};
	u8 frog4[8][8] = {{5,5,5,4,4,4,4,4},
							{5,5,1,4,4,4,4,4},
							{5,1,1,1,4,4,4,4},
							{4,4,4,1,1,4,4,4},
							{4,4,4,4,1,4,4,4},
							{4,4,4,4,1,1,4,4},
							{4,4,4,4,1,4,4,4},
							{4,4,4,4,4,4,4,4}};

	if (direction == 0)
	{
		
		arrayY = 0;
		for (tileY = 0; tileY<8; ++tileY)
		{
			arrayX = 0;
			for (tileX = 0; tileX<8; ++tileX)
			{
				setPixel(FROG_TILE_1,tileX,tileY,colors[frog1[arrayY][arrayX]]);
				setPixel(FROG_TILE_2,tileX,tileY,colors[frog2[arrayY][arrayX]]);
				setPixel(FROG_TILE_3,tileX,tileY,colors[frog3[arrayY][arrayX]]);
				setPixel(FROG_TILE_4,tileX,tileY,colors[frog4[arrayY][arrayX]]);
				++arrayX;
			}
			++arrayY;
		}
	}
	else if (direction == 1)
	{
		arrayX = 0;
		for (tileY = 0; tileY<8; ++tileY)
		{
			arrayY = 7;
			for (tileX = 0; tileX<8; ++tileX)
			{
				setPixel(FROG_TILE_1,tileX,tileY,colors[frog3[arrayY][arrayX]]);
				setPixel(FROG_TILE_2,tileX,tileY,colors[frog1[arrayY][arrayX]]);
				setPixel(FROG_TILE_3,tileX,tileY,colors[frog4[arrayY][arrayX]]);
				setPixel(FROG_TILE_4,tileX,tileY,colors[frog2[arrayY][arrayX]]);
				--arrayY;
			}
			++arrayX;
		}
	}
	else if (direction == 2)
	{
	
	}
	else if (direction == 3)
	{
	
	}
}

void moveFrog(int x, int y)
{
	setMoveableBlockPosition(FROG_BLOCK_1,x-9,y-9);
	setMoveableBlockPosition(FROG_BLOCK_2,x,y-9);
	setMoveableBlockPosition(FROG_BLOCK_3,x-9,y);
	setMoveableBlockPosition(FROG_BLOCK_4,x,y);
}
