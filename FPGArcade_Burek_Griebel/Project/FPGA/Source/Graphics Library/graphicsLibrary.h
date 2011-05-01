#ifndef GFX_LIB_H
#define GFX_LIB_H

#include "xparameters.h"
#include "xgpio.h"

//begin core output prototypes
void initGraphics();
void setPixel(u8 tileNumber, u8 x, u8 y, u8 color);
void setBackgroundBlock(u8 x, u8 y, u8 tileNumber);
void setMoveableBlock(u8 blockNumber, u8 tileNumber);
void setMoveableBlockPosition(u8 blockNumber, u16 x, u16 y);
void setMoveableBlockRowTransparency(u8 tileNumber, u8 tileRow, u8 transparency);
void mapArrayToTile(u32 storage[], u8 color_palette[], u8 tile_num);

//begin pixel array manipulation prototypes
void crotate(u32 storage[]);
void rotate(u32 source_ary[], u32 storage[]);
void cflip(u32 storage[], int x, int y);
void flip(u32 source_ary[], u32 storage[], u8 x, u8 y);
void multipleRotate(u32 source_ary[], u32 storage[], u8 timesToRotate);
/************************************************************************
*	For these functions to work you must store your tile graphics using
*	our standard of four bit indexed color in an array of size 8, storing
*	a u32 variable to specify the colors in a single row. An example is 
*	shown below of a blue diamond on a black background with a red center.
*
*	u8 color_palette[3] = {BLACK,BLUE,RED};
*	u32 circleGraphic[8] = {	0x00011000,
*										0x00111100,
*										0x01111110,
*										0x11122111,
*										0x11122111,
*										0x01111110,
*										0x00111100,
*										0x00011000
*									};
*
*	When written out as a hex value, each digit in the u32 value specifies
*	the indexed color for one pixel in that row. These functions are 
*	included because it can be simpler to store complex images in this format
*	than writting individual setPixel commands to output it.
*
************************************************************************/


#define GRAPHICS_OUTPUT_CHANNEL 1
#define GRAPHICS_CLOCK_CHANNEL 2

//begin core color definitions
#define RED 0x07
#define GREEN 0x38
#define BLUE 0xC0
#define WHITE 0xFF
#define BLACK 0x00
#define YELLOW 0x3F
#define PURPLE 0xC7
#define GREY 0xAD
#define CYAN 0xE8
#define BROWN 0x14

XGpio graphicsGPIO;




#endif

