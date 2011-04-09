#define HIT_LBOUND	1
#define HIT_RBOUND	2
#define HIT_TBOUND	3
#define HIT_BBOUND	4
#define MISS			0


void reCalcFrogBounds(Frog *frog)
{
	(*frog).x0 = (*frog).x - (*frog).width /2;
	(*frog).y0 = (*frog).y - (*frog).height /2;
	(*frog).x1 = (*frog).x + (*frog).width /2;
	(*frog).y1 = (*frog).y + (*frog).height /2;
}

void reCalcEnemyBounds(Enemy *enemy)
{
	(*enemy).x0 = (*enemy).x - (*enemy).width /2;
	(*enemy).y0 = (*enemy).y - (*enemy).height /2;
	(*enemy).x1 = (*enemy).x + (*enemy).width /2;
	(*enemy).y1 = (*enemy).y + (*enemy).height /2;
}

//Determines if the x and y coordinates are inside the paddle
int classify_point(u16 x, u16 y, Enemy *e)
{

	if((x > (*e).x0) && (x < (*e).x1) && (y > (*e).y0) && (y < (*e).y1)){
		return 1;
	}else{
		return 0;
	}
}

//determines if the frog has hit a car and how
u16 find_hitBound(Frog *frog, Enemy *enemy)
{
	//recalculate lower right points for the ball and given paddle
	reCalcFrogBounds(frog);
	reCalcEnemyBounds(enemy);
	
	if(classify_point((*frog).x0, (*frog).y0, enemy) && classify_point((*frog).x0, (*frog).y1, enemy)){
		return HIT_LBOUND; //left bound collision
	}
	else if(classify_point((*frog).x1, (*frog).y0, enemy) && classify_point((*frog).x1, (*frog).y1, enemy)){
		return HIT_RBOUND; // right bound collision
	}else if(classify_point((*frog).x0, (*frog).y0, enemy) && classify_point((*frog).x1, (*frog).y0, enemy)){
		return HIT_TBOUND; // top bound collision
	}else if(classify_point((*frog).x0, (*frog).y1, enemy) && classify_point((*frog).x1, (*frog).y1, enemy)){
		return HIT_BBOUND; // bottom bound collision
	}else{
		return MISS;//no collision
	}

}

