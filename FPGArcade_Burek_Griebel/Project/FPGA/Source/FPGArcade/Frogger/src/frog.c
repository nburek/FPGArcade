#include "frog.h"

//start the graphic data for the first frog frame
u32 movingFrog1[8] = {	0x00000000,
								0x00000000,
								0x00010000,
								0x00110021,
								0x00010312,
								0x00010112,
								0x00001222,
								0x00000212};
								
u32 movingFrog2[8] = {	0x00000212,
								0x00000121,
								0x00001112,
								0x00011000,
								0x00010000,
								0x00110000,
								0x00010000,
								0x00000000};
								
u8 movingTransparencyMapUp1[8] = {0xFF,0xFF,0xEF,0xCC,0xE8,0xE8,0xF0,0xF8};
u8 movingTransparencyMapUp2[8] = {0xFF,0xFF,0xF7,0x33,0x17,0x17,0x0F,0x1F};
u8 movingTransparencyMapUp3[8] = {0xF8,0xF8,0xF0,0xE7,0xEF,0xCF,0xEF,0xFF};
u8 movingTransparencyMapUp4[8] = {0x1F,0x1F,0x0F,0xE7,0xF7,0xF3,0xF7,0xFF};

u8 movingTransparencyMapRight1[8] = {0xFF,0xFF,0xDF,0x87,0xF3,0xF8,0xF8,0xF8};
u8 movingTransparencyMapRight2[8] = {0xFF,0xFF,0xF7,0xC3,0xBF,0x0F,0x07,0x07};
u8 movingTransparencyMapRight3[8] = {0xF8,0xF8,0xF8,0xF3,0x87,0xDF,0xFF,0xFF};
u8 movingTransparencyMapRight4[8] = {0x07,0x07,0x0F,0xBF,0xC3,0xF7,0xFF,0xFF};

u8 movingTransparencyMapDown1[8] = {0xFF,0xEF,0xCF,0xEF,0xE7,0xF0,0xF8,0xF8};
u8 movingTransparencyMapDown2[8] = {0xFF,0xF7,0xF3,0xF7,0xE7,0x0F,0x1F,0x1F};
u8 movingTransparencyMapDown3[8] = {0xF8,0xF0,0xE8,0xE8,0xCC,0xEF,0xFF,0xFF};
u8 movingTransparencyMapDown4[8] = {0x1F,0x0F,0x17,0x17,0x33,0xF7,0xFF,0xFF};

u8 movingTransparencyMapLeft1[8] = {0xFF,0xFF,0xEF,0xC3,0xFD,0xF0,0xE0,0xE0};
u8 movingTransparencyMapLeft2[8] = {0xFF,0xFF,0xFB,0xE1,0xCF,0x1F,0x1F,0x1F};
u8 movingTransparencyMapLeft3[8] = {0xE0,0xE0,0xF0,0xFD,0xC3,0xEF,0xFF,0xFF};
u8 movingTransparencyMapLeft4[8] = {0x1F,0x1F,0x1F,0xCF,0xE1,0xFB,0xFF,0xFF};

//start the graphic data for the second frog frame
u32 sittingFrog1[8] = {	0x00000000,
								0x00000000,
								0x00000000,
								0x00010021,
								0x00110312,
								0x00010112,
								0x00011222,
								0x00000212};
								
u32 sittingFrog2[8] = {	0x00011212,
								0x00010121,
								0x00110012,
								0x00010000,
								0x00000000,
								0x00000000,
								0x00000000,
								0x00000000};

								
u8 sittingTransparencyMapUp1[8] = {0xFF,0xFF,0xFF,0xEC,0xC8,0xE8,0xE0,0xF8};
u8 sittingTransparencyMapUp2[8] = {0xFF,0xFF,0xFF,0x37,0x13,0x17,0x07,0x1F};
u8 sittingTransparencyMapUp3[8] = {0xE0,0xE8,0xCC,0xEF,0xFF,0xFF,0xFF,0xFF};
u8 sittingTransparencyMapUp4[8] = {0x07,0x17,0x33,0xF7,0xFF,0xFF,0xFF,0xFF};

u8 sittingTransparencyMapRight1[8] = {0xFF,0xFF,0xFB,0xF0,0xFE,0xFC,0xF8,0xF8};
u8 sittingTransparencyMapRight2[8] = {0xFF,0xFF,0xEF,0x87,0xBF,0x0F,0x07,0x07};
u8 sittingTransparencyMapRight3[8] = {0xF8,0xF8,0xFC,0xFE,0xF0,0xFB,0xFF,0xFF};
u8 sittingTransparencyMapRight4[8] = {0x07,0x07,0x0F,0xBF,0x87,0xEF,0xFF,0xFF};

u8 sittingTransparencyMapDown1[8] = {0xFF,0xFF,0xFF,0xFF,0xEF,0xCC,0xE8,0xE0};
u8 sittingTransparencyMapDown2[8] = {0xFF,0xFF,0xFF,0xFF,0xF7,0x33,0x17,0x07};
u8 sittingTransparencyMapDown3[8] = {0xF8,0xE0,0xE8,0xC8,0xEC,0xFF,0xFF,0xFF};
u8 sittingTransparencyMapDown4[8] = {0x1F,0x07,0x17,0x13,0x37,0xFF,0xFF,0xFF};

u8 sittingTransparencyMapLeft1[8] = {0xFF,0xFF,0xF7,0xE1,0xFD,0xF0,0xE0,0xE0};
u8 sittingTransparencyMapLeft2[8] = {0xFF,0xFF,0xDF,0x0F,0x7F,0x3F,0x1F,0x1F};
u8 sittingTransparencyMapLeft3[8] = {0xE0,0xE0,0xF0,0xFD,0xE1,0xF7,0xFF,0xFF};
u8 sittingTransparencyMapLeft4[8] = {0x1F,0x1F,0x3F,0x7F,0x0F,0xDF,0xFF,0xFF};

u8 playerOneColors[] = {BLACK,GREEN,YELLOW,PURPLE};
u8 playerTwoColors[] = {BLACK,YELLOW,PURPLE,RED};

/*****************************************************************************/
/**
*
* Sets the frogs initial position, speed, direction, and life count
*
*
* @param		None
*
* @return	None
*
* @note		None
*
****************************************************************************/
void initFrog(Frog* frog){
	(*frog).x = 320;
	(*frog).y = 320;
	
	(*frog).x_spd = 8;
	(*frog).y_spd = 8;
	
	(*frog).dir = 1;
	(*frog).lives = 3;

}
/*****************************************************************************/
/**
*
* Places the frog off screen and clears visible map
*
*
* @param		Frog* frog - The frog object needs to be cleared from window frame
*
* @return	None
*
* @note		None
*
****************************************************************************/
void clearFrog(Frog* frog)
{
	u8 i;
	for (i = 0; i<4; ++i){
		setMoveableBlockPosition(	FROG_BLOCK_1 +i,	640,	0);
	}

}
/*****************************************************************************/
/**
*
* Handles reseting the frog and decreasing his lives when he is killed
*
*
* @param		Frog* frog - The frog object that was killed
*
* @return	None
*
* @note		None
*
****************************************************************************/
void dieFrog(Frog* frog)
{
	--(*frog).lives;
	(*frog).x = 320;
	(*frog).y = 320;
	int i,j;
	for (i = 7; i>=0; --i)
	{
		for (j=0; j<60;++j)
			outputFrogger(1,i%4,1);
	}
}


/*****************************************************************************/
/**
*
* Handles outputting the frog graphic, using the proper animation frame, 
* direction and color.
*
* @param		u8 animationFrame - Which frame you want to be outputted
* @param		u8 direction - Which direction the frog is facing
* @param		u8 player - Which frog you want to output (selects different colors)
*
* @return	None
*
* @note		animationFrame: 0 - sitting still, 1 - jumping
*				Directions: 0 - up, 1 - right, 2 - down, 3 - left
*				Player: 1 - first player, 2 - second player
*
****************************************************************************/
void outputFrogger(u8 animationFrame, u8 direction, u8 player)
{

	u8 *colors;
	
	int arrayX, arrayY, tileX, tileY;
	
	u32 *frog1;
	u32 *frog2;
	
	u8 *transparencyMap1;
	u8 *transparencyMap2;
	u8 *transparencyMap3;
	u8 *transparencyMap4;
	
	for (arrayX = 0; arrayX<4; ++arrayX)
		setMoveableBlock(FROG_BLOCK_1+arrayX,FROG_TILE_1+arrayX);
	/*
	setMoveableBlock(FROG_BLOCK_1, FROG_TILE_1);
	setMoveableBlock(FROG_BLOCK_2, FROG_TILE_2);
	setMoveableBlock(FROG_BLOCK_3, FROG_TILE_3);
	setMoveableBlock(FROG_BLOCK_4, FROG_TILE_4);*/
	
	//select which color palette to use
	if (player == 1)
		colors = playerOneColors;
	else
		colors = playerTwoColors;
	
	//select which animation graphic to use
	if (animationFrame == 0) // sitting image
	{
		frog1 = sittingFrog1;
		frog2 = sittingFrog2;
	}
	else if (animationFrame == 1) //moving image
	{
		frog1 = movingFrog1;
		frog2 = movingFrog2;
	}
	
	u32 temp[8];
	
	//start outputting graphics
	if (direction == UP)
	{
		mapArrayToTile(frog1,colors,FROG_TILE_1);
		flip(frog1,temp,0,1);
		mapArrayToTile(temp,colors,FROG_TILE_2);
		mapArrayToTile(frog2,colors,FROG_TILE_3);
		flip(frog2,temp,0,1);
		mapArrayToTile(temp,colors,FROG_TILE_4);
		
		if (animationFrame == 0 )
		{
			transparencyMap1 = sittingTransparencyMapUp1;
			transparencyMap2 = sittingTransparencyMapUp2;
			transparencyMap3 = sittingTransparencyMapUp3;
			transparencyMap4 = sittingTransparencyMapUp4;
		}
		else if (animationFrame == 1)
		{
			transparencyMap1 = movingTransparencyMapUp1;
			transparencyMap2 = movingTransparencyMapUp2;
			transparencyMap3 = movingTransparencyMapUp3;
			transparencyMap4 = movingTransparencyMapUp4;
		}
		
	}
	else if (direction == RIGHT)
	{
		rotate(frog2,temp);
		mapArrayToTile(temp,colors,FROG_TILE_1);
		cflip(temp,1,0);
		mapArrayToTile(temp,colors,FROG_TILE_3);
		rotate(frog1,temp);
		mapArrayToTile(temp,colors,FROG_TILE_2);
		cflip(temp,1,0);
		mapArrayToTile(temp,colors,FROG_TILE_4);
		
		if (animationFrame == 0 )
		{
			transparencyMap1 = sittingTransparencyMapRight1;
			transparencyMap2 = sittingTransparencyMapRight2;
			transparencyMap3 = sittingTransparencyMapRight3;
			transparencyMap4 = sittingTransparencyMapRight4;
		}
		else if (animationFrame == 1)
		{
			transparencyMap1 = movingTransparencyMapRight1;
			transparencyMap2 = movingTransparencyMapRight2;
			transparencyMap3 = movingTransparencyMapRight3;
			transparencyMap4 = movingTransparencyMapRight4;
		}
		
	}
	else if (direction == DOWN)
	{
		multipleRotate(frog2,temp,2);
		mapArrayToTile(temp,colors,FROG_TILE_2);
		cflip(temp,0,1);
		mapArrayToTile(temp,colors,FROG_TILE_1);
		multipleRotate(frog1,temp,2);
		mapArrayToTile(temp,colors,FROG_TILE_4);
		cflip(temp,0,1);
		mapArrayToTile(temp,colors,FROG_TILE_3);

		if (animationFrame == 0 )
		{
			transparencyMap1 = sittingTransparencyMapDown1;
			transparencyMap2 = sittingTransparencyMapDown2;
			transparencyMap3 = sittingTransparencyMapDown3;
			transparencyMap4 = sittingTransparencyMapDown4;
		}
		else if (animationFrame == 1)
		{
			transparencyMap1 = movingTransparencyMapDown1;
			transparencyMap2 = movingTransparencyMapDown2;
			transparencyMap3 = movingTransparencyMapDown3;
			transparencyMap4 = movingTransparencyMapDown4;
		}
		
	}
	else if (direction == LEFT)
	{
		multipleRotate(frog1,temp,3);
		mapArrayToTile(temp,colors,FROG_TILE_3);
		cflip(temp,1,0);
		mapArrayToTile(temp,colors,FROG_TILE_1);
		multipleRotate(frog2,temp,3);
		mapArrayToTile(temp,colors,FROG_TILE_4);
		cflip(temp,1,0);
		mapArrayToTile(temp,colors,FROG_TILE_2);

		if (animationFrame == 0 )
		{
			transparencyMap1 = sittingTransparencyMapLeft1;
			transparencyMap2 = sittingTransparencyMapLeft2;
			transparencyMap3 = sittingTransparencyMapLeft3;
			transparencyMap4 = sittingTransparencyMapLeft4;
		}
		else if (animationFrame == 1)
		{
			transparencyMap1 = movingTransparencyMapLeft1;
			transparencyMap2 = movingTransparencyMapLeft2;
			transparencyMap3 = movingTransparencyMapLeft3;
			transparencyMap4 = movingTransparencyMapLeft4;
		}
	}
	
	//start outputting the transparency map
	int i = 0;
	for (i=0; i<8; ++i)
	{
		setMoveableBlockRowTransparency(FROG_BLOCK_1,i,transparencyMap1[i]);
		setMoveableBlockRowTransparency(FROG_BLOCK_2,i,transparencyMap2[i]);
		setMoveableBlockRowTransparency(FROG_BLOCK_3,i,transparencyMap3[i]);
		setMoveableBlockRowTransparency(FROG_BLOCK_4,i,transparencyMap4[i]);
	}
}

/*****************************************************************************/
/**
*
* Moves the frog blocks to the position stored in the frog structure
*
*
* @param		Frog* frog - The frog structure to get the position from
*
* @return	None
*
* @note		None
*
****************************************************************************/
void moveFrog(Frog* frog)
{
	setMoveableBlockPosition(	FROG_BLOCK_1,	(*frog).x-8,	(*frog).y-8);
	setMoveableBlockPosition(	FROG_BLOCK_2,	(*frog).x,		(*frog).y-8);
	setMoveableBlockPosition(	FROG_BLOCK_3,	(*frog).x-8,	(*frog).y);
	setMoveableBlockPosition(	FROG_BLOCK_4,	(*frog).x,		(*frog).y);
}

/*****************************************************************************/
/**
*
* Draws the specified number of lives out to the screen
*
*
* @param		u8 lives - the number of lives to draw
*
* @return	None
*
* @note		None
*
****************************************************************************/
void drawLives(u8 lives)
{
	
	int i;
	
	if(lives <= 6){
	
		setBackgroundBlock(24 + lives,16, 10); // fill black
		
		for(i = 1; i < lives; ++i){
		
			setBackgroundBlock(24 + i,16, frogLifeTILE); // fill with froggy life
			
		}
	}else{
	
		setBackgroundBlock(25,16, frogLifeTILE);
		setBackgroundBlock(26,16, 30); //white x
		outputDigits(lives, 28, 16);
	}

}


