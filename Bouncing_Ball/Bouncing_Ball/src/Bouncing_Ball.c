#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"

/************************** Constant Definitions ****************************/

/*
 * The following constant is used to wait after an LED is turned on to make
 * sure that it is visible to the human eye.  This constant might need to be
 * tuned for faster or slower processor speeds.
 */
#define LOOP_DELAY	  10000

/* following constant is used to determine which channel of the GPIO is
 * used if there are 2 channels supported in the GPIO.
 */
#define BLOCK_CHANNEL 1
#define PADDLE_CHANNEL 2

#define GPIO_BLOCK_BITWIDTH	19	/* This is the width of the GPIO */
#define GPIO_PADDLE_BITWIDTH	18	/* This is the width of the GPIO */

#define JOYSTICK_1_CHANNEL 1
#define JOYSTICK_2_CHANNEL 2

#define printf xil_printf	/* A smaller footprint printf */


/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
 
 #define STAGE_WIDTH 640
 #define STAGE_HEIGHT 480


/**************************** Type Definitions ******************************/

typedef struct{

	u16 x;
	u16 y;//centered at upper left corner
	u16 width;
	u16 height;
	u16 x_spd;
	u16 y_spd;

}Ball;
Ball ball; 

typedef struct{//yeah, its the same as the ball for right now, but that may change

	u16 x;
	u16 y;
	u16 width;
	u16 height;
	u16 x_spd;
	u16 y_spd;

}Paddle;
Paddle paddle1, paddle2; 

typedef struct{

	u16 x;
	u16 y;//centered at upper left corner

	u8 btn1;
	u8 btn2;
	u8 btn3;


}joystick;
joystick joy1, joy2; 

/***************** Macros (Inline Functions) Definitions *******************/


/************************** Function Prototypes ****************************/

void initBall(){

	ball.x = 300;
	ball.y = 200;
	ball.width = 30;
	ball.height = 30;
	ball.x_spd = 1;
	ball.y_spd = 1;
}

void initJoysticks();
void getJoystickData(joystick *jstkData, int joystickChannel);


/************************** Variable Definitions **************************/

/*
 * The following are declared globally so they are zeroed and so they are
 * easily accessible from a debugger
 */
XGpio GpioOutput; /* The driver instance for GPIO Device configured as O/P */
XGpio joystickGPIO;

/*****************************************************************************/
/**
* Main function to call the example.This function is not included if the
* example is generated from the TestAppGen test tool.
*
* @param	None
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful
*
* @note		None
*
******************************************************************************/
int main(void)
{
	u32 Data;
	volatile int Delay;
	int Status;
	
	initBall();
	initJoysticks();
	
	/*ball.x = 0; //the blocks X coord
	ball.y = 0; //the blocks Y coord
	ball.x_spd = 1; //should it move left or right (1=right, -1=left)
	ball.y_spd = 1; //should it move up or down (1=down, -1=up)
	*/

	/*
	 * Initialize the GPIO driver so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h
	 */
	 Status = XGpio_Initialize(&GpioOutput, XPAR_BLOCK_OUTPUT_DEVICE_ID);
	 if (Status != XST_SUCCESS)  {
		  return XST_FAILURE;
	 }

	

	 /*
	  * Set the direction for all signals to be outputs
	  */
	 XGpio_SetDataDirection(&GpioOutput, BLOCK_CHANNEL, 0x0);
	 XGpio_SetDataDirection(&GpioOutput, PADDLE_CHANNEL, 0x0);

	 /*
	  * Set the GPIO outputs to low
	  */
	 XGpio_DiscreteWrite(&GpioOutput, BLOCK_CHANNEL, 0x0);
	 XGpio_DiscreteWrite(&GpioOutput, PADDLE_CHANNEL, 0x17CBE);

	while (1)
	{
		//move the blocks
		ball.x += ball.x_spd;
		ball.y += ball.y_spd;

		//reverse the direction when it hits the edge
		if (ball.x >= (STAGE_WIDTH - ball.width) || ball.x<=0)
			ball.x_spd *= -1;
		
		if (ball.y >= (STAGE_HEIGHT - ball.height) || ball.y<=0)
			ball.y_spd *= -1;
		
		/*
		 * Since both the X and Y coord's are sent on the same signal
		 * vector we must combine the two into one variable to be 
		 * written out. The 10 most significant bits are the X position
		 * and the lower 10 bits are the Y position.
		 */
		Data = (ball.x<<9) | ball.y;
		
		//write out the values to the GIOP, which sends them to the VGA Driver
		XGpio_DiscreteWrite(&GpioOutput, BLOCK_CHANNEL, Data);
		
		getJoystickData(&joy1, JOYSTICK_1_CHANNEL);
		XGpio_DiscreteWrite(&GpioOutput, PADDLE_CHANNEL, (joy1.y>>1));
		
		
		for (Delay = 0; Delay < LOOP_DELAY; ++Delay); //delay for a while
		
	}

	return XST_SUCCESS;
}



/*****************************************************************************/
/**
*
* This function initializes the joystick GPIO device and channels
*
*
* @param		None
*
* @return	None
*
* @note		None
*
****************************************************************************/
void initJoysticks()
{
	XGpio_Initialize(&joystickGPIO, XPAR_JOYSTICK_GPIO_DEVICE_ID);
	XGpio_SetDataDirection(&joystickGPIO, JOYSTICK_1_CHANNEL, 0xFFFFFFFF);
	XGpio_SetDataDirection(&joystickGPIO, JOYSTICK_2_CHANNEL, 0xFFFFFFFF);
}


/*****************************************************************************/
/**
*
* This function reads the data from joystick GPIO device on the channel 
* specified. It then seperates that data out and stores it back into the
* joystick structure that was passed by reference.
*
*
* @param	jstkData is where the joystick data is saved back to
*
* @param	joystickChannel is the channel that is read on the joystick GPIO 
*
* @return	None
*
* @note		None
*
****************************************************************************/
void getJoystickData(joystick *jstkData, int joystickChannel)
{
	u32 Data;
	u8 Buttons;
	
	Data = XGpio_DiscreteRead(&joystickGPIO, joystickChannel);
	
	(*jstkData).x = (Data & 0x3FF); //read bits 0-9 into X
	
	(*jstkData).y = (Data>>10) & 0x3FF;
	
	(*jstkData).btn1 = (Data >> 20) & 0x1;
	
	(*jstkData).btn2 = (Data >> 21) & 0x1;
	
	(*jstkData).btn3 = (Data >> 22) & 0x1;
}


