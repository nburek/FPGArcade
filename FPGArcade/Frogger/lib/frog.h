
#define FROG_TILE_1 60
#define FROG_TILE_2 61
#define FROG_TILE_3 62
#define FROG_TILE_4 63

#define FROG_BLOCK_1 0
#define FROG_BLOCK_2 1
#define FROG_BLOCK_3 2
#define FROG_BLOCK_4 3

typedef struct frog_struct{

	u16 x, x0, x1;
	u16 y, y0, y1;
	u16 width, height;
	u8 x_spd;
	u8 y_spd;
	
	u8 dir;
	u8 alive;
	
	u16 jump_delay;

}Frog;

void initFrog(Frog* frog){
	(*frog).x = 320;
	(*frog).y = 320;
	(*frog).width = 16;
	(*frog).height = 16;
	
	(*frog).x_spd = 8;
	(*frog).y_spd = 8;
	
	(*frog).dir = 1;
	(*frog).alive = 1;
	
	(*frog).jump_delay = 30;
}

#define LEFT 3
#define RIGHT 0
#define UP 1
#define DOWN 2

u32 movingFrog1[8] = {	0x00000000,
								0x00000000,
								0x00010000,
								0x00110021,
								0x00010312,
								0x00010112,
								0x00001222,
								0x00000212};
u32 movingFrog2[8] = {	0x00000000,
								0x00000000,
								0x00001000,
								0x22001100,
								0x21301000,
								0x21101000,
								0x22210000,
								0x22200000};
u32 movingFrog3[8] = {	0x00000212,
								0x00000121,
								0x00001112,
								0x00011000,
								0x00010000,
								0x00110000,
								0x00010000,
								0x00000000};
u32 movingFrog4[8] = {	0x22200000,
								0x22100000,
								0x21110000,
								0x00011000,
								0x00001000,
								0x00001100,
								0x00001000,
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

u32 sittingFrog1[8] = {	0x00000000,
								0x00000000,
								0x00000000,
								0x00010021,
								0x00110312,
								0x00010112,
								0x00011222,
								0x00000212};

u32 sittingFrog2[8] = {	0x00000000,
								0x00000000,
								0x00000000,
								0x22001000,
								0x21301100,
								0x21101000,
								0x22211000,
								0x22200000};
u32 sittingFrog3[8] = {	0x00011212,
								0x00010121,
								0x00110012,
								0x00010000,
								0x00000000,
								0x00000000,
								0x00000000,
								0x00000000};

u32 sittingFrog4[8] = {	0x22211000,
								0x22101000,
								0x21001100,
								0x00001000,
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

/*
	animationFrame: 0 - sitting still, 1 - jumping
	Directions: 0 - up, 1 - right, 2 - down, 3 - left
	Player: 1 - first player, 2 - second player
*/
void outputFrogger(u8 animationFrame, u8 direction, u8 player)
{

	u8 *colors;
	
	int arrayX, arrayY, tileX, tileY;
	
	u32 *frog1;
	u32 *frog2;
	u32 *frog3;
	u32 *frog4;
	
	u8 *transparencyMap1;
	u8 *transparencyMap2;
	u8 *transparencyMap3;
	u8 *transparencyMap4;
	
	setMoveableBlock(FROG_BLOCK_1, FROG_TILE_1);
	setMoveableBlock(FROG_BLOCK_2, FROG_TILE_2);
	setMoveableBlock(FROG_BLOCK_3, FROG_TILE_3);
	setMoveableBlock(FROG_BLOCK_4, FROG_TILE_4);
	
	if (player == 1)
		colors = playerOneColors;
	else
		colors = playerTwoColors;
	
	if (animationFrame == 0) // sitting image
	{
		frog1 = sittingFrog1;
		frog2 = sittingFrog2;
		frog3 = sittingFrog3;
		frog4 = sittingFrog4;
	}
	else if (animationFrame == 1) //moving image
	{
		frog1 = movingFrog1;
		frog2 = movingFrog2;
		frog3 = movingFrog3;
		frog4 = movingFrog4;
	}
	
	u32 temp[8];
	
	if (direction == UP)
	{
		mapArrayToTile(frog1,colors,FROG_TILE_1);
		mapArrayToTile(frog2,colors,FROG_TILE_2);
		mapArrayToTile(frog3,colors,FROG_TILE_3);
		mapArrayToTile(frog4,colors,FROG_TILE_4);
		
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
		rotate(frog3,temp);
		mapArrayToTile(temp,colors,FROG_TILE_1);
		rotate(frog1,temp);
		mapArrayToTile(temp,colors,FROG_TILE_2);
		rotate(frog4,temp);
		mapArrayToTile(temp,colors,FROG_TILE_3);
		rotate(frog2,temp);
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
		multipleRotate(frog4,temp,2);
		mapArrayToTile(temp,colors,FROG_TILE_1);
		multipleRotate(frog3,temp,2);
		mapArrayToTile(temp,colors,FROG_TILE_2);
		multipleRotate(frog2,temp,2);
		mapArrayToTile(temp,colors,FROG_TILE_3);
		multipleRotate(frog1,temp,2);
		mapArrayToTile(temp,colors,FROG_TILE_4);

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
		multipleRotate(frog2,temp,3);
		mapArrayToTile(temp,colors,FROG_TILE_1);
		multipleRotate(frog4,temp,3);
		mapArrayToTile(temp,colors,FROG_TILE_2);
		multipleRotate(frog1,temp,3);
		mapArrayToTile(temp,colors,FROG_TILE_3);
		multipleRotate(frog3,temp,3);
		mapArrayToTile(temp,colors,FROG_TILE_4);

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
	
	
	int i = 0;
	for (i=0; i<8; ++i)
	{
		setMoveableBlockRowTransparency(FROG_BLOCK_1,i,transparencyMap1[i]);
		setMoveableBlockRowTransparency(FROG_BLOCK_2,i,transparencyMap2[i]);
		setMoveableBlockRowTransparency(FROG_BLOCK_3,i,transparencyMap3[i]);
		setMoveableBlockRowTransparency(FROG_BLOCK_4,i,transparencyMap4[i]);
	}
}

void moveFrog(Frog* frog)
{
	setMoveableBlockPosition(	FROG_BLOCK_1,	(*frog).x-8,	(*frog).y-8);
	setMoveableBlockPosition(	FROG_BLOCK_2,	(*frog).x,		(*frog).y-8);
	setMoveableBlockPosition(	FROG_BLOCK_3,	(*frog).x-8,	(*frog).y);
	setMoveableBlockPosition(	FROG_BLOCK_4,	(*frog).x,		(*frog).y);
}
