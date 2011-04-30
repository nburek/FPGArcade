#ifndef ENEMIES_H
#define ENEMIES_H

#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"

#define logTile1 17
#define logTile2 18
#define logTile3 19
#define logTile4 20
#define logTile5 21
#define logTile6 22

#define turtleTile1 23
#define turtleTile2 24
#define turtleTile3 25
#define turtleTile4 26

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

//start function prototypes
void initMovingObjects();
void drawObjectOnScreen(u8 x, u8 y, u8 tile1, u8 tile2, u8 tile3, u8 tile4);
void moveRow(u8 row);
void writeOutCarTile(u32 graphic1[], u32 graphic2[], u8 tile1, u8 tile2, u8 tile3, u8 tile4);
void outputCarTiles();


#endif 
