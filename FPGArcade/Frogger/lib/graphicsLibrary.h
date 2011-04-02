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
	
	Data = tileRow | (tileNumber<<4) | (transparency<<7) | (0x20000000);
	
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

