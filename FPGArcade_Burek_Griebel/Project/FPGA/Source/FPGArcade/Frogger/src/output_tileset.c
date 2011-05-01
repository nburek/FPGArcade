#include "output_tileset.h"

/* Which tiles are used to store which images:
0 - 9 : Numbers
10: Black Tile
11: Blue/water
12: Border Tile
13-16: Purple Tile
17-22: logs
23-26: turtles
27 - 30: reserved
31: Green Grass
32 - 35: Fancy Frog
36-39: Time Bar
40-43: Race Car
44-47: Bull Dozer
48-51: Purple Car
52-59: Truck
60-63: Frog
*/

/*****************************************************************************/
/**
*
* Outputs all of the graphics needed for the background and other misc things.
* It also draws the background.
*
*
* @param		None
*
* @return	None
*
* @note		None
*
****************************************************************************/
void drawBackground()
{

	u8 color_palette[6] = {PURPLE,BLUE,RED,BLACK,GREEN,GREY};

	u32 digits[10][8] = {
		{0x33555333,0x35335533,0x55333553,0x55333553,0x55333553,0x35533533,0x33555333,0x33333333}, 
		{0x33553333,0x35553333,0x33553333,0x33553333,0x33553333,0x33553333,0x55555533,0x33333333}, 
		{0x35555533,0x55333553,0x33335553,0x33555533,0x35555333,0x55533333,0x55555553,0x33333333}, 
		{0x35555553,0x33335533,0x33355333,0x33555533,0x33333553,0x55333553,0x35555533,0x33333333}, 
		{0x33355533,0x33555533,0x35535533,0x55335533,0x55555553,0x33335533,0x33335533,0x33333333}, 
		{0x55555533,0x55333333,0x55555533,0x33333553,0x33333553,0x55333553,0x35555533,0x33333333}, 
		{0x33555533,0x35533333,0x55333333,0x55555533,0x55333553,0x55333553,0x35555533,0x33333333}, 
		{0x55555553,0x55333553,0x33335533,0x33355333,0x33553333,0x33553333,0x33553333,0x33333333}, 
		{0x35555333,0x55333533,0x55533533,0x35555333,0x53355553,0x53333553,0x35555533,0x33333333}, 
		{0x35555533,0x55333553,0x55333553,0x35555553,0x33333553,0x33335533,0x35555333,0x33333333}};

	u32 dirt1[8] = {0x00010012, 
					  0x00000001, 
					  0x01000000, 
					  0x12100000, 
					  0x01001001, 
					  0x00012100, 
					  0x00001000, 
					  0x00100330};

	u32 dirt2[8] = {0x10000000, 
					  0x00001000, 
					  0x20012100, 
					  0x30001000, 
					  0x21000000, 
					  0x10000000, 
					  0x00000000, 
					  0x33033333};

	u32 dirt3[8] = {0x30330033, 
					  0x00000000, 
					  0x00100001, 
					  0x01210012, 
					  0x00100001, 
					  0x00000000, 
					  0x00010000, 
					  0x00121001};

	u32 dirt4[8] = {0x03300333, 
					  0x03000000, 
					  0x00000100, 
					  0x10001210, 
					  0x00000100, 
					  0x20100000, 
					  0x21210000, 
					  0x20100000};
					  
	u32 grass[8] =  {0x34444443, 
						  0x44444344, 
						  0x44444444, 
						  0x43224444, 
						  0x44344443, 
						  0x44444444, 
						  0x43443224, 
						  0x44444344};
	
	
	int i = 0;
	int ii = 0;
	
	//set the entire background to the black tile
	for (i = 0; i<80; ++i)
		for (ii = 0; ii<60; ++ii)
			setBackgroundBlock(i,ii,10);
	
	//output numbers
	for (i = 0; i<10; ++i)
		mapArrayToTile(digits[i], color_palette, i);
			
	

	//border tile
	for (i = 0; i<8; ++i){
		for (ii = 0; ii<8; ++ii){
			if((i != 0 && ii !=0) && (i != 7 && ii !=7)){
				setPixel(12,i,ii,RED);
			}else{
				setPixel(12,i,ii,WHITE);
			}
		}
	}
	
	//water tile
	for (i = 0; i<8; ++i){
		for (ii = 0; ii<8; ++ii){
			setPixel(11,i,ii,BLUE);
		}
	}
	
	// Red and White Xs tile
	for (i = 1; i<7; ++i){
	
		setPixel(27,i,i,RED);
		setPixel(27,(6 - i),i,RED);
		
		setPixel(30,i,i,WHITE);
		setPixel(30,(6 - i),i,WHITE);
	}

	//create life graphic
	u8 life_palette[] = {BLACK,GREEN,YELLOW,PURPLE};
	u32 life[8] = 	 {0x00000000, 
						  0x01032301, 
						  0x01222221, 
						  0x00222220, 
						  0x00222220, 
						  0x01122211, 
						  0x01000001, 
						  0x01000001};
	mapArrayToTile(life, life_palette, 28);
	
	//create road
	for (i = 26; i<54; ++i)
		for (ii = 19; ii<41; ++ii)
			setBackgroundBlock(i,ii,10);
			
	//top/bottom border
	for (i = 25; i<55; ++i){
		setBackgroundBlock(i,17,borderTILE);
		setBackgroundBlock(i,41,borderTILE);
	}
	
	//left/right border
	for (i = 17; i<42; ++i){
		setBackgroundBlock(25,i,borderTILE);
		setBackgroundBlock(54,i,borderTILE);
	}
	
	//draw water
	for (i = 26; i<54; ++i){
		for (ii = 19; ii<30; ++ii){
			setBackgroundBlock(i,ii,waterTILE);
			setBackgroundBlock(i,ii,waterTILE);
		}
	}
	
	//create grass tile
	mapArrayToTile(grass, color_palette, 31);
	//draw grass on screen
	int x;
	for (x = 26; x<54; ++x)
	{
		setBackgroundBlock(x,18,31);
		if ((x%6!=3) && (x%6!= 4))
		{
			setBackgroundBlock(x,19,31);
			setBackgroundBlock(x,20,31);
		}
	}
	
	//create dirt tile
	mapArrayToTile(dirt1, color_palette, dirtTILE1);
	mapArrayToTile(dirt2, color_palette, dirtTILE2);
	mapArrayToTile(dirt3, color_palette, dirtTILE3);
	mapArrayToTile(dirt4, color_palette, dirtTILE4);
	
	//draw dirt on screen
	for (x = 26; x<53; ++x)
	{
		setBackgroundBlock(x,40,dirtTILE2);
		setBackgroundBlock(x+1,40,dirtTILE1);
		setBackgroundBlock(x,39,dirtTILE4);
		setBackgroundBlock(x+1,39,dirtTILE3);
		
		setBackgroundBlock(x,30,dirtTILE2);
		setBackgroundBlock(x+1,30,dirtTILE1);
		setBackgroundBlock(x,29,dirtTILE4);
		setBackgroundBlock(x+1,29,dirtTILE3);
	}
	
}




