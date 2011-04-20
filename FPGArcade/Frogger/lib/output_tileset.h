/*
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

void drawBackground();


void drawBackground()
{

	u8 color_palette[5] = {PURPLE,BLUE,RED,BLACK,GREEN};
	
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
	
	// x tile
	for (i = 1; i<7; ++i){
	
		setPixel(27,i,i,RED);
		setPixel(27,(6 - i),i,RED);
	}
	
	for (i = 1; i<7; ++i){
	
		setPixel(29,i,i,BLUE);
		setPixel(29,(6 - i),i,BLUE);
	}

	u8 life_palette[] = {BLACK,GREEN,YELLOW,PURPLE};
	//create life
	u32 life[8] = 	 {0x00000000, 
						  0x01032301, 
						  0x01222221, 
						  0x00222220, 
						  0x00222220, 
						  0x01122211, 
						  0x01000001, 
						  0x01000001};
	mapArrayToTile(life, life_palette, 28);
	
	//create black border
	for (i = 26; i<54; ++i)
		for (ii = 19; ii<41; ++ii)
			setBackgroundBlock(i,ii,1);
			
	//top/bottom border
	for (i = 25; i<55; ++i){
		setBackgroundBlock(i,17,12);
		setBackgroundBlock(i,41,12);
	}
	
	//left/right border
	for (i = 17; i<42; ++i){
		setBackgroundBlock(25,i,12);
		setBackgroundBlock(54,i,12);
	}
	
	//draw water
	for (i = 26; i<54; ++i){
		for (ii = 19; ii<30; ++ii){
			setBackgroundBlock(i,ii,11);
			setBackgroundBlock(i,ii,11);
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
	mapArrayToTile(dirt1, color_palette, 13);
	mapArrayToTile(dirt2, color_palette, 14);
	mapArrayToTile(dirt3, color_palette, 15);
	mapArrayToTile(dirt4, color_palette, 16);
	
	//draw dirt on screen
	for (x = 26; x<53; ++x)
	{
		setBackgroundBlock(x,40,14);
		setBackgroundBlock(x+1,40,13);
		setBackgroundBlock(x,39,16);
		setBackgroundBlock(x+1,39,15);
		
		setBackgroundBlock(x,30,14);
		setBackgroundBlock(x+1,30,13);
		setBackgroundBlock(x,29,16);
		setBackgroundBlock(x+1,29,15);
	}
	
}




