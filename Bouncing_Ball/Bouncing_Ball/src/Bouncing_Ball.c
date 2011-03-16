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

/* 
 *following constant is used to determine which channel of the GPIO is
 * used if there are 2 channels supported in the GPIO.
 */
#define BLOCK_CHANNEL 1
#define PADDLE_CHANNEL 2

#define GPIO_BLOCK_BITWIDTH	19	/* This is the width of the GPIO */
#define GPIO_PADDLE_BITWIDTH	18	/* This is the width of the GPIO */

#define JOYSTICK_1_CHANNEL 1
#define JOYSTICK_2_CHANNEL 2

#define printf xil_printf	/* A smaller footprint printf */

//to classify collision
#define LBOUND 1
#define RBOUND 2
#define MISS   0


/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
 
 #define STAGE_WIDTH 640
 #define STAGE_HEIGHT 480


/**************************** Type Definitions ******************************/

typedef struct ball_struct{

	u16 x;
	u16 y;//centered at upper left corner
	u16 x1;
	u16 y1;
	u16 width;
	u16 height;
	u16 x_spd;
	u16 y_spd;

}Ball;
 

typedef struct paddle_struct{//yeah, its the same as the ball for right now, but that may change

	u16 x;
	u16 y;
	u16 x1;
	u16 y1;
	u16 width;
	u16 height;
	u16 x_spd;
	u16 y_spd;

}Paddle;


typedef struct joystick_struct{

	u16 x;
	u16 y;//centered at upper left corner

	u8 btn1;
	u8 btn2;
	u8 btn3;
	
}Joystick;

/***************** Macros (Inline Functions) Definitions *******************/


/************************** Function Prototypes ****************************/

void initBall(Ball*);
void initPaddle(Paddle*);
void reCalcBallBounds(Ball *ball);
void reCalcPaddleBounds(Paddle *paddle);
int classify_point(u16 x, u16 y, Paddle*);
u16 find_hitBound(Ball*, Paddle*);
void initJoysticks();
void getJoystickData(Joystick *jstkData, int joystickChannel);


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
	volatile int longDelayCount = 0;
	int Status;
	
	Ball ball;
	Paddle paddle1, paddle2; 
	Joystick joy1, joy2;

	//initialize data structures
	initBall(&ball);
	initJoysticks();
	initPaddle(&paddle2);
	initPaddle(&paddle1);
	

	//initialize the block and paddle GPIO
	XGpio_Initialize(&GpioOutput, XPAR_BLOCK_OUTPUT_DEVICE_ID);

	//Set the direction for block and paddle signals to be outputs
	XGpio_SetDataDirection(&GpioOutput, BLOCK_CHANNEL, 0x0);
	XGpio_SetDataDirection(&GpioOutput, PADDLE_CHANNEL, 0x0);

	//delay for a while so that the screen can initialize and turn on
	for (longDelayCount=0; longDelayCount<100000; ++longDelayCount);
	
	while (1)
	{
		//get joystick data and map it to paddles
		getJoystickData(&joy1, JOYSTICK_1_CHANNEL);
		paddle2.y = (joy1.y) >> 1;
		getJoystickData(&joy2, JOYSTICK_2_CHANNEL);
		paddle1.y = (joy2.y) >> 1;
		
		//move the ball
		ball.x += ball.x_spd;
		ball.y += ball.y_spd;

		
		//check to see if the ball hits the paddles
		u16 hit_value = find_hitBound(&ball, &paddle2) | find_hitBound(&ball, &paddle1);

		//!watch for special casses such as when leftbound is less than paddle and rightbound is greater
		switch (hit_value){
		
			case LBOUND:case RBOUND:
				ball.x_spd *= -1;
				break;		
			case MISS:default:
				if (ball.x >= STAGE_WIDTH || ball.x<= -ball.width){
					initBall(&ball);
					longDelayCount = 0; //set to 0 so that the game will delay for a while
					ball.y = ((joy1.y & 0x1)<<1) | (joy2.y & 0x1); //set a random ball speed between 0 and 3

				}
				if (ball.y >= STAGE_HEIGHT || ball.y<= -ball.height){
					initBall(&ball);
					longDelayCount = 0; //set to 0 so that the game will delay for a while
					ball.y = ((joy1.y & 0x1)<<1) | (joy2.y & 0x1); //set a random ball speed between 0 and 3

				}
				break;
		
		}
		
		/*
		* Since both the X and Y coord's are sent on the same signal
		* vector we must combine the two into one variable to be 
		* written out. The 10 most significant bits are the X position
		* and the lower 10 bits are the Y position.
		*/
		Data = (ball.x<<9) | ball.y;
		
		//write out the values to the GIOP, which sends them to the VGA Driver
		XGpio_DiscreteWrite(&GpioOutput, BLOCK_CHANNEL, Data);
		
		//write out the paddle positions
		Data = (paddle1.y<<9) | paddle2.y;
		XGpio_DiscreteWrite(&GpioOutput, PADDLE_CHANNEL, Data);
		
		for (;longDelayCount < 100000; ++longDelayCount);
		
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
void getJoystickData(Joystick *jstkData, int joystickChannel)
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

void initBall(Ball *ball)
{

	(*ball).x = 300;
	(*ball).y = 200;
	(*ball).width = 30;
	(*ball).height = 30;
	
	(*ball).x1 = (*ball).x + (*ball).width;
	(*ball).y1 = (*ball).y + (*ball).height;//absolute points
	
	(*ball).x_spd = 1;
	(*ball).y_spd = 1;
}

void initPaddle(Paddle *paddle)
{

	(*paddle).x = 625;
	(*paddle).y = 100;
	(*paddle).width = 15;
	(*paddle).height = 100;
	
	(*paddle).x1 = (*paddle).x + (*paddle).width;
	(*paddle).y1 = (*paddle).y + (*paddle).height;
	
	(*paddle).x_spd = 1;
	(*paddle).y_spd = 1;
}

//determine the lower right coordinate of the ball
void reCalcBallBounds(Ball *ball)
{
	(*ball).x1 = (*ball).x + (*ball).width;
	(*ball).y1 = (*ball).y + (*ball).height;
}

//determine the lower right coordinates of the paddle
void reCalcPaddleBounds(Paddle *paddle)
{
	(*paddle).x1 = (*paddle).x + (*paddle).width;
	(*paddle).y1 = (*paddle).y + (*paddle).height;
}

//Determines if the x and y coordinates are inside the paddle
int classify_point(u16 x, u16 y, Paddle *p)
{

	if((x > (*p).x) && (x < (*p).x1) && (y > (*p).y) && (y < (*p).y1)){
		return 1;
	}else{
		return 0;
	}
}

//determines if the ball has hit the paddle and where
u16 find_hitBound(Ball *ball, Paddle *paddle)
{
	//recalculate lower right points for the ball and given paddle
	reCalcBallBounds(ball);
	reCalcPaddleBounds(paddle);
	
	if(classify_point((*ball).x, (*ball).y, paddle) && classify_point((*ball).x, (*ball).y1, paddle)){
		return LBOUND; //left bound collision
	}
	else if(classify_point((*ball).x1, (*ball).y, paddle) && classify_point((*ball).x1, (*ball).y1, paddle)){
		return RBOUND; // right bound collision
	}else{
		return MISS;//no collision
	}

}


