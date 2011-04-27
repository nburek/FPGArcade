#define raceCarTile1 40
#define raceCarTile2 41
#define raceCarTile3 42
#define raceCarTile4 43

#define bullDozerTile1 44
#define bullDozerTile2 45
#define bullDozerTile3 46
#define bullDozerTile4 47

#define purpleCarTile1 48
#define purpleCarTile2 49
#define purpleCarTile3 50
#define purpleCarTile4 51

#define truckTile1 52
#define truckTile2 53
#define truckTile3 54
#define truckTile4 55
#define truckTile5 56
#define truckTile6 57
#define truckTile7 58
#define truckTile8 59

#define turtleTile1 23
#define turtleTile2 24
#define turtleTile3 25
#define turtleTile4 26

#define logTile1 17
#define logTile2 18
#define logTile3 19
#define logTile4 20
#define logTile5 21
#define logTile6 22

//starting and ending borders tiles
#define minXTile 25
#define maxXTile 54

#define FIRST_ROW_Y 37

enum MOVING_TYPES
{
	Race_Car,
	Truck,
	Bull_Dozer,
	Purple_Car,
	Blank_Row,
	Turtle,
	Log,
	Turtle2,
	Log2
};

s8 movingObjectsWidth[9] = {2,4,2,2,0,4,4,4, 6};
s8 direction[9] = {1,-1,1,-1,0,-1,1,-1,1};
u16 movingObjectsX[9][4];

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



//moves all the objects on that row and then redraws the row
void moveRow(u8 row)
{
	int x;
	u8 y = FIRST_ROW_Y - 2*row;
	
	//set all tiles in row to blue or black
	u8 backgroundColorTile = (y<29)?11:10;
	for (x = minXTile+1; x<maxXTile; ++x)
	{
		setBackgroundBlock(x,y,backgroundColorTile);
		setBackgroundBlock(x,y+1,backgroundColorTile);
	}
		
	for (x = 0; x<4; ++x)
	{
		movingObjectsX[row][x] += direction[row];
		
		if (movingObjectsX[row][x] < 20)
			movingObjectsX[row][x] = 59;
		else if (movingObjectsX[row][x] > 59)
			movingObjectsX[row][x] = 20;
		
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


