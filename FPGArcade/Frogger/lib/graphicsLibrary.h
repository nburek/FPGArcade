#include "xparameters.h"
#include "xgpio.h"

//void setPixel(u8 tileNumber, u8 x, u8 y, u8 color);
//void setBackgroundBlock(u8 x, u8 y, u8 tileNumber);
//void setMoveableBlock(u8 blockNumber, u8 tileNumber);
//void setMoveableBlockPosition(u8 blockNumber, u16 x, u16 y);
//void setMoveableBlockRowTransparency(u8 tileNumber, u8 tileRow, u8 transparency);
//void initGraphics();


#define GRAPHICS_OUTPUT_CHANNEL 1
#define GRAPHICS_CLOCK_CHANNEL 2

#define RED 0x07
#define GREEN 0x38
#define BLUE 0xC0
#define WHITE 0xFF
#define BLACK 0x00
#define YELLOW 0x3F
#define PURPLE 0xC7
#define GREY 0xAD
#define CYAN 0xE8

XGpio graphicsGPIO;


void setPixel(u8 tileNumber, u8 x, u8 y, u8 color)
{
	u32 Data;
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 0);
	
	Data = color | (y<<8) | (x<<11) | (tileNumber<<14);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_OUTPUT_CHANNEL, Data);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 1);
	
	
}

void setBackgroundBlock(u8 x, u8 y, u8 tileNumber)
{
	u32 Data;
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 0);
	
	Data = x | (y<<7) | (tileNumber << 13) | (0x80000000);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_OUTPUT_CHANNEL, Data);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 1);
}

void setMoveableBlock(u8 blockNumber, u8 tileNumber)
{
	u32 Data;
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 0);
	
	Data = blockNumber | (tileNumber<<4) | (0x60000000);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_OUTPUT_CHANNEL, Data);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 1);
	
	
}

void setMoveableBlockPosition(u8 blockNumber, u16 x, u16 y)
{
	u32 Data;
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 0);
	
	Data = x | (y<<10) | (blockNumber<<19) | (0x40000000);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_OUTPUT_CHANNEL, Data);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 1);
}

void setMoveableBlockRowTransparency(u8 tileNumber, u8 tileRow, u8 transparency)
{
	u32 Data;
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 0);
	
	Data = tileRow | (tileNumber<<3) | (transparency<<7) | (0x20000000);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_OUTPUT_CHANNEL, Data);
	
	XGpio_DiscreteWrite(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 1);
}

void initGraphics()
{
	//initialize GPIO
	XGpio_Initialize(&graphicsGPIO, XPAR_GRAPHICS_GPIO_DEVICE_ID);

	//Set the direction to be outputs
	XGpio_SetDataDirection(&graphicsGPIO, GRAPHICS_OUTPUT_CHANNEL, 0x0);
	XGpio_SetDataDirection(&graphicsGPIO, GRAPHICS_CLOCK_CHANNEL, 0x0);
}

void mapArrayToTile(u32 storage[], u8 color_palette[], u8 tile_num){

	u8 i, j;
	for(j = 0; j < 8; ++j){

		u8 shift = 28;
		for(i = 0; i < 8; ++i){

			u8 color = (storage[j] >> shift)  &0x0000000F;
			setPixel(tile_num, i, j, color_palette[color]);
			shift -= 4;

		}
	}
}

//rotates a tile clockwise
void rotate(u32 source_ary[], u32 storage[])
{

	int i, j;

	for(i = 0; i < 8; ++i)
	{
		storage[i] = 0;
		for(j = 7; j >= 0; --j)
		{
			u32 value = (source_ary[j] >> (7 - i)*4)  &0x0000000F;

			storage[i] |= ((value) << j*4);
		}

	}


}

void crotate(u32 storage[])
{

	u32 t_ary[8];
	u8 i;
	for(i = 0; i < 8; ++i){
		t_ary[i] = storage[i];
	}

	rotate(t_ary, storage);
}

void multipleRotate(u32 source_ary[], u32 storage[], u8 timesToRotate)
{
	u8 i;
	for (i = 0; i<timesToRotate; ++i)
	{
		if (i==0)
			rotate(source_ary,storage);
		else
			crotate(storage);
	}
}


//flips the graphics array
//treat x and y as booleans, where x is flip over x axis and y is flip over y axis
void flip(u32 source_ary[], u32 storage[], u8 x, u8 y)
{

	int i, j;

	//flip over x axis
	for (i = 0; i<8; ++i)
	{
		storage[i] = (x==1)?source_ary[7-i]:source_ary[i];
	}
	
	//flip over y axis
	if (y==1)
	{
		for (i = 0; i<8; ++i)
		{
			u32 temp = 0;
			for (j = 0; j<=28; j+= 4)
			{
				temp = temp | (((storage[i] >> j) & 0xF)<<(28-j));
			}
			storage[i] = temp;
		}
	}

}


void cflip(u32 storage[], int x, int y)
{
	u32 t_ary[8];
	int i;
	for(i = 0; i < 8; ++i){
		t_ary[i] = storage[i];
	}

	flip(t_ary, storage, x, y);
}

