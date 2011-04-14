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

void createDirtTile();
void drawDirt();
void createGrassTile();
void drawGrass();
void createLoggy();
void drawLoggy(int x, int y);
void drawBackground();


void drawBackground(){

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
	createGrassTile();
	drawGrass();
	
	createDirtTile();
	drawDirt();
	
	createLoggy();
	drawLoggy(0, 0);
}

void createGrassTile()
{

	//green grass -31

	u8 color_palette[3] = {BLACK,RED,GREEN};
	
	u32 ary1[8] = 	 {0x02222220, 
						  0x22222022, 
						  0x22222222, 
						  0x20112222, 
						  0x22022220, 
						  0x22222222, 
						  0x20220112, 
						  0x22222022};
						  
	mapArrayToTile(ary1, color_palette, 31);

}
void drawGrass()
{
	
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

}


void createDirtTile()
{

	//13 - 16

	/*Value: 0         Index Value: 3
	Value: ff        Index Value: 2
	Value: f70000    Index Value: 1
	Value: f70097    Index Value: 0*/

	u8 color_palette[4] = {PURPLE,BLUE,RED, BLACK};
	
	
	u32 ary1[8] = 	 {0x00010012, 
					  0x00000001, 
					  0x01000000, 
					  0x12100000, 
					  0x01001001, 
					  0x00012100, 
					  0x00001000, 
					  0x00100330};

	u32 ary2[8] = 	 {0x10000000, 
					  0x00001000, 
					  0x20012100, 
					  0x30001000, 
					  0x21000000, 
					  0x10000000, 
					  0x00000000, 
					  0x33033333};

	u32 ary3[8] = 	 {0x30330033, 
					  0x00000000, 
					  0x00100001, 
					  0x01210012, 
					  0x00100001, 
					  0x00000000, 
					  0x00010000, 
					  0x00121001};

	u32 ary4[8] = 	 {0x03300333, 
					  0x03000000, 
					  0x00000100, 
					  0x10001210, 
					  0x00000100, 
					  0x20100000, 
					  0x21210000, 
					  0x20100000};

					  

	mapArrayToTile(ary1, color_palette, 13);
	mapArrayToTile(ary2, color_palette, 14);
	mapArrayToTile(ary3, color_palette, 15);
	mapArrayToTile(ary4, color_palette, 16);

}

void drawDirt(){
	
	
	int i;
	for (i = 26; i<53; ++i){
		setBackgroundBlock(i,40,14);
		setBackgroundBlock(i+1,40,13);
		setBackgroundBlock(i,39,16);
		setBackgroundBlock(i+1,39,15);
		
		setBackgroundBlock(i,30,14);
		setBackgroundBlock(i+1,30,13);
		setBackgroundBlock(i,29,16);
		setBackgroundBlock(i+1,29,15);
	}
	
}

void createLoggy(){

	/*Value: 470000    Index Value: 1
	Value: 4f68de    Index Value: 0
	Value: f7dede    Index Value: 2
	*/

//	u8 color_palette[4] = {RED,BLUE, WHITE};

	/*mapArrayToTile(ary1, color_palette, 17, 0);
	mapArrayToTile(ary2, color_palette, 18, 0);
	mapArrayToTile(ary3, color_palette, 19, 0);
	
	mapArrayToTile(ary1, color_palette, 20, 0);
	mapArrayToTile(ary2, color_palette, 21, 0);
	mapArrayToTile(ary3, color_palette, 22, 0);*/
	
	

}
void drawLoggy(int x, int y){
	
		setBackgroundBlock(x,30,14);
	
}
