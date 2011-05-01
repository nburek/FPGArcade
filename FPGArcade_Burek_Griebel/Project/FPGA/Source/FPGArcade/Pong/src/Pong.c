#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "joystickLibrary.h"
#include "graphicsLibrary.h"

//start function prototypes
void drawPaddle1();
void erasePaddle1();
void drawPaddle2();
void erasePaddle2();

//start declaring counters for timing
int ballMovementCounter = 0;
int BALL_MOVEMENT_DELAY = 5000;
int paddleMovementCounter = 10000;
#define PADDLE_MOVEMENT_DELAY 35000
int ballSpdIncreaseCounter = 0;
#define BALL_SPEED_INCREASE_DELAY 1

int ballX = 10, ballY = 10, ballSpdY=1, ballSpdX=1;
int paddle1Y = 0, paddle2Y = 0;
int paddle1X = 0, paddle2X = 79;

/*****************************************************************************/
/**
* Main function that starts the pong game.
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
	
	Joystick joy1,joy2;

	initJoysticks();

	initGraphics();
	
	
	//create a white tile
	int i, ii;
	for (i = 0; i<8; ++i)
		for (ii = 0; ii<8; ++ii)
			setPixel(1,i,ii,WHITE);
			
	//start making the ball
	for (i = 3; i<5; ++i)
		for (ii = 1; ii<7; ++ii)
		{
			setPixel(2,i,ii,WHITE);
			setPixel(2,ii,i,WHITE);
		}
	setPixel(2,2,2,WHITE);
	setPixel(2,2,5,WHITE);
	setPixel(2,5,2,WHITE);
	setPixel(2,5,5,WHITE);
	setMoveableBlock(0, 2);
	setMoveableBlockRowTransparency(0, 0, 0xFF);
	setMoveableBlockRowTransparency(0, 1, 0xE7);
	setMoveableBlockRowTransparency(0, 2, 0xC3);
	setMoveableBlockRowTransparency(0, 3, 0x81);
	setMoveableBlockRowTransparency(0, 4, 0x81);
	setMoveableBlockRowTransparency(0, 5, 0xC3);
	setMoveableBlockRowTransparency(0, 6, 0xE7);
	setMoveableBlockRowTransparency(0, 7, 0xFF); //finished making the ball
	
	setMoveableBlockPosition(0, ballX, ballY); //draw the ball once
	
	//draw the two paddles
	for (i = paddle1Y; i<(paddle1Y+10) && i<80; ++i)
					setBackgroundBlock(0,i,1);
	for (i = paddle2Y; i<(paddle2Y+10) && i<80; ++i)
					setBackgroundBlock(79,i,1);
	
	//start game loop
	while (1)
	{
		++ballMovementCounter;
		++paddleMovementCounter;
		
		if(ballMovementCounter > BALL_MOVEMENT_DELAY)
		{
			ballMovementCounter = 0;
			ballX += ballSpdX;
			ballY += ballSpdY;
			
			if (ballY == 0 || ballY == 472)
				ballSpdY *= -1;
			
			if (ballX == 0) //left side lost 1 point
			{
				ballX = 628;
				ballSpdIncreaseCounter = 0;
				BALL_MOVEMENT_DELAY = 10000;
				
				if (paddle1X>0)
				{
					erasePaddle1();
					--paddle1X;
					drawPaddle1();
				}
				else
				{
					erasePaddle2();
					--paddle2X;
					if (paddle2X<40)
						paddle2X = 40;
					drawPaddle2();
				}
				
				
					
			}
			else if (ballX>=(paddle1X*8) && ballX<=(paddle1X*8+8)) //start collision detection with left paddle
			{
				if ((ballY+4)>(paddle1Y*8) && (ballY+4)<=((paddle1Y+10)*8))
				{
					ballSpdX = 1;
					++ballSpdIncreaseCounter;
				}
			}
				

			if (ballX == 632) // right side lost 1 point
			{
				ballX = 4;
				ballSpdIncreaseCounter = 0;
				BALL_MOVEMENT_DELAY = 10000;
				
				if (paddle2X<79)
				{
					erasePaddle2();
					++paddle2X;
					drawPaddle2();
				}
				else
				{
					erasePaddle1();
					++paddle1X;
					if (paddle1X>40)
						paddle1X = 40;
					drawPaddle1();
				}
				
				
				
			}
			else if ((ballX+8)>=(paddle2X*8) && (ballX+8)<=(paddle2X*8+8)) //start collision detection with right paddle
			{
				
				if ((ballY+4)>=(paddle2Y*8) && (ballY+4)<=((paddle2Y+10)*8))
				{
					ballSpdX = -1;
					++ballSpdIncreaseCounter;
				}
			}
			
			setMoveableBlockPosition(0, ballX, ballY);
			
		}
	
	
		if (paddleMovementCounter > PADDLE_MOVEMENT_DELAY)
		{
			paddleMovementCounter = 0;
			
			updateJoystick(&joy1,JOYSTICK_1_CHANNEL);
			
			if (joy1.y > 750)
			{
				--paddle1Y;
				if (paddle1Y<0)
					paddle1Y = 0;
			}
			else if (joy1.y < 250)
			{
				++paddle1Y;
				if (paddle1Y>50)
					paddle1Y = 50;
			}
			
			if (joy1.y>750 || joy1.y<250)
			{
				setBackgroundBlock(paddle1X,paddle1Y-1,0);
				setBackgroundBlock(paddle1X,paddle1Y+10,0);
				
				drawPaddle1();
			}
			
			updateJoystick(&joy2,JOYSTICK_2_CHANNEL);
			
			if (joy2.y > 750)
			{
				--paddle2Y;
				if (paddle2Y<0)
					paddle2Y = 0;
			}
			else if (joy2.y < 250)
			{
				++paddle2Y;
				if (paddle2Y>50)
					paddle2Y = 50;
			}
			
			if (joy2.y>750 || joy2.y<250)
			{
				
				setBackgroundBlock(paddle2X,paddle2Y-1,0);
				setBackgroundBlock(paddle2X,paddle2Y+10,0);
				
				drawPaddle2();
			}
			
			
		}
		
		if (ballSpdIncreaseCounter>=BALL_SPEED_INCREASE_DELAY)
		{
			ballSpdIncreaseCounter = 0;
			BALL_MOVEMENT_DELAY -= 500;
			if (BALL_MOVEMENT_DELAY < 500)
				BALL_MOVEMENT_DELAY = 500;
		}
		
		
		
	} //end infinite game loop

	return XST_SUCCESS;
}


void drawPaddle1()
{
	int i;
	for (i = paddle1Y; i<(paddle1Y+10) && i<80; ++i)
		setBackgroundBlock(paddle1X,i,1);
}

void erasePaddle1()
{
	int i;
	for (i = paddle1Y; i<(paddle1Y+10) && i<80; ++i)
		setBackgroundBlock(paddle1X,i,0);
}

void drawPaddle2()
{
	int i;
	for (i = paddle2Y; i<(paddle2Y+10) && i<80; ++i)
		setBackgroundBlock(paddle2X,i,1);
}

void erasePaddle2()
{
	int i;
	for (i = paddle2Y; i<(paddle2Y+10) && i<80; ++i)
		setBackgroundBlock(paddle2X,i,0);
}






