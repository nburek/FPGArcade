
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
	(*frog).x = 270;
	(*frog).y = 320;
	(*frog).width = 16;
	(*frog).height = 16;
	
	(*frog).x_spd = 8;
	(*frog).y_spd = 8;
	
	(*frog).dir = 1;
	(*frog).alive = 1;
	
	(*frog).jump_delay = 30;
}

