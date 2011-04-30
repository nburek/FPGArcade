
/*****************************************************************************/
/**
*
* Checks if the frog has collided with one of the moving objects in a row
*
*
* @param		u16 carRow[] - The block X positions of the moving objects in the row
* @param		u8 objW - specifies the width of each object (in blocks)
* @param		u16 frogX - the X position (in pixels) of the frog
*
* @return	Returns 1 if the frog is hitting an object in the row or 0 if it isn't
*
* @note		None
*
****************************************************************************/
u8 checkCollision(u16 carRow[],u8 objW, u16 frogX)
{
	
	int i, j;
	
	u16 bFrogX = frogX /8; //find which block the frog is on
	
	for(i = 0; i < 4; ++i) //for each of the moving objects in the array
	{

		//check for a collision with the current object
		for(j = 0; j <= objW; ++j)
		{
			if( bFrogX == (carRow[i] + j))
				return 1;
		}
	}
	
	return 0; //the frog isn't hitting anything

}

