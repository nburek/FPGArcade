#ifndef FROG_H
#define FROG_H

#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"

#define FROG_TILE_1 60
#define FROG_TILE_2 61
#define FROG_TILE_3 62
#define FROG_TILE_4 63

#define FROG_BLOCK_1 0
#define FROG_BLOCK_2 1
#define FROG_BLOCK_3 2
#define FROG_BLOCK_4 3

#define LEFT 3
#define RIGHT 0
#define UP 1
#define DOWN 2

#define frogLifeTILE 28

typedef struct frog_struct{

	u16 x;
	u16 y;
	u8 x_spd;
	u8 y_spd;
	
	u8 dir;
	u8 lives;
	

}Frog;

//start function prototypes
void initFrog(Frog* frog);
void dieFrog(Frog* frog);
void outputFrogger(u8 animationFrame, u8 direction, u8 player);
void moveFrog(Frog* frog);
void drawLives(u8 lives);


#endif 
