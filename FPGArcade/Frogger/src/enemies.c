#include "enemies.h"

s8 movingObjectsWidth[9] = {2,4,2,2,0,4,4,4, 6}; //width of moving objects (in blocks)
s8 direction[9] = {1,-1,1,-1,0,-1,1,-1,1}; //which direction objects in a row are moving
u16 movingObjectsX[9][4]; //x position of the moving objects in each row

//quick fix to access globals form main
s8 getMovingObjectsWidth(u8 index){
	return movingObjectsWidth[index];
}
s8 getDirection(u8 index){
	return direction[index];
}
u16* getMovingObjectsX(u8 lane){
	return movingObjectsX[lane];
}
/*****************************************************************************/
/**
*
* Initializes all the moving objects by assigning an x position to each
*
*
* @param		None
*
* @return	None
*
* @note		None
*
****************************************************************************/
void initMovingObjects()
{
	int row, xPos, obj;
	for (row = 0; row<9; ++row)
	{
		for (obj = 0,xPos=22; obj<4; ++obj,xPos+=10)
		{
		movingObjectsX[row][obj] = xPos;
		}
	}
 
}

/*****************************************************************************/
/**
*
* Sets the blocks starting at the specified x,y position to display the tiles
* for the moving object. Used to draw objects that are 2x2 blocks in size.
*
*
* @param		u8 x - Specifies where the left side of the graphic should be
* @param		u8 y - Specifies where the top of the graphic should be
* @param		u8 tile[1-4] - Specifies the tile to use when outputting the 
*					corresponding blocks.
*
* @return	None
*
* @note		None
*
****************************************************************************/
void drawObjectOnScreen(u8 x, u8 y, u8 tile1, u8 tile2, u8 tile3, u8 tile4)
{
	if (x>=minXTile && x<maxXTile-1)
	{
		setBackgroundBlock( x+1, y, tile2);
		setBackgroundBlock( x+1, y+1, tile4);
	}
	
	if (x>minXTile && x<maxXTile)
	{
		setBackgroundBlock( x, y, tile1);
		setBackgroundBlock( x, y+1, tile3);
	}
}



/*****************************************************************************/
/**
*
* Will move all the moving objects in the specified row and then redraw that
* row.
*
*
* @param		u8 row - which row you want to move
*
* @return	None
*
* @note		None
*
****************************************************************************/
void moveRow(u8 row)
{
	int x;
	u8 y = FIRST_ROW_Y - 2*row;
	
	
	u8 backgroundColorTile = (y<29)?11:10; //select color for water or road
	
	//blank out the row to either blue or black
	for (x = minXTile+1; x<maxXTile; ++x)
	{
		setBackgroundBlock(x,y,backgroundColorTile);
		setBackgroundBlock(x,y+1,backgroundColorTile);
	}
		
	//start moving and redrawing all the moving objects in the row
	for (x = 0; x<4; ++x)
	{
	
		//start moving the object
		movingObjectsX[row][x] += direction[row];
		
		if (movingObjectsX[row][x] < 20)
			movingObjectsX[row][x] = 59;
		else if (movingObjectsX[row][x] > 59)
			movingObjectsX[row][x] = 20;
		
		//redraw the object
		switch (row)
		{
			case Race_Car:
				drawObjectOnScreen(movingObjectsX[row][x],y,raceCarTile1,raceCarTile2,raceCarTile3,raceCarTile4);
				break;
			case Truck:
				drawObjectOnScreen(movingObjectsX[row][x],y,truckTile1,truckTile2,truckTile5,truckTile6);
				drawObjectOnScreen(movingObjectsX[row][x]+2,y,truckTile3,truckTile4,truckTile7,truckTile8);
				break;
			case Bull_Dozer:
				drawObjectOnScreen(movingObjectsX[row][x],y,bullDozerTile1,bullDozerTile2,bullDozerTile3,bullDozerTile4);
				break;
			case Purple_Car:
				drawObjectOnScreen(movingObjectsX[row][x],y,purpleCarTile1,purpleCarTile2,purpleCarTile3,purpleCarTile4);
				break;
			case Turtle:
			case Turtle2:
				drawObjectOnScreen(movingObjectsX[row][x],y,turtleTile1,turtleTile2,turtleTile3,turtleTile4);
				drawObjectOnScreen(movingObjectsX[row][x]+2,y,turtleTile1,turtleTile2,turtleTile3,turtleTile4);
				break;
			case Log:
				drawObjectOnScreen(movingObjectsX[row][x],y,logTile1,logTile2,logTile4,logTile5);
				drawObjectOnScreen(movingObjectsX[row][x]+2,y,logTile2,logTile3,logTile5,logTile6);
				break;
			case Log2:
				drawObjectOnScreen(movingObjectsX[row][x],y,logTile1,logTile2,logTile4,logTile5);
				drawObjectOnScreen(movingObjectsX[row][x]+2,y,logTile2,logTile2,logTile5,logTile5);
				drawObjectOnScreen(movingObjectsX[row][x]+4,y,logTile2,logTile3,logTile5,logTile6);
				break;
			
		}
		
	}
}


/*****************************************************************************/
/**
*
* This function is used to output the moving object graphics to the tiles 
* that they need to be stored in.
*
*
* @param		u32 graphic1[] - The first graphic to be output
* @param		u32 graphic2[] - The second graphic to be output
* @param		u8 tile1 - The tile to output the flipped graphic 1 to
* @param		u8 tile2 - The tile to output the flipped graphic 2 to
* @param		u8 tile3 - The tile to output graphic 1 to
* @param		u8 tile4 - The tile to output graphic 2 to
*
* @return	None
*
* @note		None
*
****************************************************************************/
void writeOutCarTile(u32 graphic1[], u32 graphic2[], u8 tile1, u8 tile2, u8 tile3, u8 tile4)
{
	u8 carColors[10] = {BLACK,PURPLE,RED,YELLOW,GREY,GREEN,CYAN,PURPLE,BLUE,BROWN};
	
	u32 temp[8];
	mapArrayToTile(graphic1, carColors, tile3);
	mapArrayToTile(graphic2, carColors, tile4);
	flip(graphic1, temp, 1,0);
	mapArrayToTile(temp, carColors, tile1);
	flip(graphic2, temp, 1,0);
	mapArrayToTile(temp, carColors, tile2);
}

/*****************************************************************************/
/**
*
* Outputs all the moving objects graphics data to the tiles they need to be
* stored in.
*
*
* @param		none
*
* @return	None
*
* @note		None
*
****************************************************************************/
void outputCarTiles()
{
	int x, y;

	u32 raceCar1[8] = {
				0x03232323,
				0x11111133,
				0x00333333,
				0x00010000,
				0x02222200,
				0x02222200,
				0x02222200,
				0x00000000};

	u32 raceCar2[8] = {
				0x31113333,
				0x11133330,
				0x33333300,
				0x00010000,
				0x02222200,
				0x02222200,
				0x00000000,
				0x00000000};

	u32 bullDozer1[8] = {
				0x04455545,
				0x04444455,
				0x00444444,
				0x00500050,
				0x04242424,
				0x04242424,
				0x00000000,
				0x00000000};

	u32 bullDozer2[8] = {
				0x44004200,
				0x45004440,
				0x44004200,
				0x05554440,
				0x00004200,
				0x00004440,
				0x00000000,
				0x00000000};	
	
	u32 truck1[8] = {
				0x00024444,
				0x00024444,
				0x00024444,
				0x00002444,
				0x00000055,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 truck2[8] = {
				0x42444444,
				0x42444444,
				0x40444444,
				0x40444444,
				0x50055500,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 truck3[8] = {
				0x44444444,
				0x44444444,
				0x44444444,
				0x44444444,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 truck4[8] = {
				0x44444400,
				0x44444400,
				0x44444400,
				0x44444400,
				0x00555000,
				0x00000000,
				0x00000000,
				0x00000000};
				

	u32 purpleCar1[8] = {
				0x67776677,
				0x63776677,
				0x67777667,
				0x06777770,
				0x00033000,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 purpleCar2[8] = {
				0x77666700,
				0x77666700,
				0x67777760,
				0x07777700,
				0x00333000,
				0x00000000,
				0x00000000,
				0x00000000};
				
	u32 turtle1[8] = {
				0x88888888,
				0x88888888,
				0x88885888,
				0x88855588,
				0x88888522,
				0x88888222,
				0x88452222,
				0x85552222};
				
	u32 turtle2[8] = {
				0x88888888,
				0x88888888,
				0x88885888,
				0x88855588,
				0x22258888,
				0x22228888,
				0x22222885,
				0x22222258};
				
	u32 log1[8] = {
				0x88888888, 
				0x88888888, 
				0x88888888, 
				0x88899999, 
				0x89999994, 
				0x89944999, 
				0x99999999, 
				0x99999999};

	u32 log2[8] = {
				0x88888888, 
				0x88888888, 
				0x88888888, 
				0x99899998, 
				0x99999499, 
				0x99999999, 
				0x99999999, 
				0x99944999};

	u32 log3[8] = {
				0x88888888, 
				0x88888888, 
				0x88888888, 
				0x99944488, 
				0x99444448, 
				0x99499948, 
				0x99499944, 
				0x94999994};
		  
	writeOutCarTile(raceCar1,raceCar2,raceCarTile1,raceCarTile2,raceCarTile3,raceCarTile4);
	writeOutCarTile(bullDozer1,bullDozer2,bullDozerTile1,bullDozerTile2,bullDozerTile3,bullDozerTile4);
	writeOutCarTile(purpleCar1,purpleCar2,purpleCarTile1,purpleCarTile2,purpleCarTile3,purpleCarTile4);
	writeOutCarTile(truck1,truck2,truckTile1,truckTile2,truckTile5,truckTile6);
	writeOutCarTile(truck3,truck4,truckTile3,truckTile4,truckTile7,truckTile8);
	writeOutCarTile(turtle1,turtle2,turtleTile3,turtleTile4,turtleTile1,turtleTile2);
	writeOutCarTile(log1,log2,logTile4,logTile5,logTile1,logTile2);
	writeOutCarTile(log3,log3,logTile6,logTile6,logTile3,logTile3);
	
	
	
}
