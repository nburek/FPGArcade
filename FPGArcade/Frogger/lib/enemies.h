#define raceCarTile1 40
#define raceCarTile2 41
#define raceCarTile3 42
#define raceCarTile4 43

#define bullDozerTile1 44
#define bullDozerTile2 45
#define bullDozerTile3 46
#define bullDozerTile4 47

#define purpleCarTile1 48
#define purpleCarTile2 49
#define purpleCarTile3 50
#define purpleCarTile4 51

#define truckTile1 52
#define truckTile2 53
#define truckTile3 54
#define truckTile4 55
#define truckTile5 56
#define truckTile6 57
#define truckTile7 58
#define truckTile8 59

typedef struct enemy_struct{

	u16 x, x0, x1;
	u16 y, y0, y1;
	u16 width, height;
	u8 x_spd;
	u8 y_spd;
	
	u8 dir;
	u8 alive;
	
	u16 jump_delay;

}Enemy;

enum CAR_TYPES
{
	race_car,
	bull_dozer,
	truck,
	purple_car
};

typedef struct Car
{
	enum CAR_TYPES type;
	u8 positionX;
	u8 positionY;
}Car;

#define raceCarY 38
#define bullDozerY 34
#define truckY 36
#define purpleCarY 32

void initCar(Car newCar, enum CAR_TYPES carType, u8 position)
{
	newCar.positionX = position;
	newCar.type = carType;
	if (carType == race_car)
		newCar.positionY = raceCarY;
	else if (carType == bull_dozer)
		newCar.positionY = bullDozerY;
	else if (carType == truck)
		newCar.positionY = truckY;
	else if (carType == purple_car)
		newCar.positionY = purpleCarY;
}

void outputCarTiles()
{
	u8 carColors[8] = {BLACK,PURPLE,RED,YELLOW,GREY,GREEN,CYAN,PURPLE};
	int x, y;

	u8 raceCar1[8][8] = {
				{0, 3, 2, 3, 2, 3, 2, 3},
				{1, 1, 1, 1, 1, 1, 3, 3},
				{0, 0, 3, 3, 3, 3, 3, 3},
				{0, 0, 0, 1, 0, 0, 0, 0},
				{0, 2, 2, 2, 2, 2, 0, 0},
				{0, 2, 2, 2, 2, 2, 0, 0},
				{0, 2, 2, 2, 2, 2, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};

	u8 raceCar2[8][8] = {
				{3, 1, 1, 1, 3, 3, 3, 3},
				{1, 1, 1, 3, 3, 3, 3, 0},
				{3, 3, 3, 3, 3, 3, 0, 0},
				{0, 0, 0, 1, 0, 0, 0, 0},
				{0, 2, 2, 2, 2, 2, 0, 0},
				{0, 2, 2, 2, 2, 2, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};

	u8 bullDozer1[8][8] = {
				{0, 4, 4, 5, 5, 5, 4, 5},
				{0, 4, 4, 4, 4, 4, 5, 5},
				{0, 0, 4, 4, 4, 4, 4, 4},
				{0, 0, 5, 0, 0, 0, 5, 0},
				{0, 4, 2, 4, 2, 4, 2, 4},
				{0, 4, 2, 4, 2, 4, 2, 4},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};

	u8 bullDozer2[8][8] = {
				{4, 4, 0, 0, 4, 2, 0, 0},
				{4, 5, 0, 0, 4, 4, 4, 0},
				{4, 4, 0, 0, 4, 2, 0, 0},
				{0, 5, 5, 5, 4, 4, 4, 0},
				{0, 0, 0, 0, 4, 2, 0, 0},
				{0, 0, 0, 0, 4, 4, 4, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};	
				
	u8 truck1[8][8] = {
				{0, 0, 0, 2, 4, 4, 4, 4},
				{0, 0, 0, 2, 4, 4, 4, 4},
				{0, 0, 0, 2, 4, 4, 4, 4},
				{0, 0, 0, 0, 2, 4, 4, 4},
				{0, 0, 0, 0, 0, 0, 5, 5},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};

	u8 truck2[8][8] = {
				{4, 2, 4, 4, 4, 4, 4, 4},
				{4, 2, 4, 4, 4, 4, 4, 4},
				{4, 0, 4, 4, 4, 4, 4, 4},
				{4, 0, 4, 4, 4, 4, 4, 4},
				{5, 0, 0, 5, 5, 5, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};

	u8 truck3[8][8] = {
				{4, 4, 4, 4, 4, 4, 4, 4},
				{4, 4, 4, 4, 4, 4, 4, 4},
				{4, 4, 4, 4, 4, 4, 4, 4},
				{4, 4, 4, 4, 4, 4, 4, 4},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};

	u8 truck4[8][8] = {
				{4, 4, 4, 4, 4, 4, 0, 0},
				{4, 4, 4, 4, 4, 4, 0, 0},
				{4, 4, 4, 4, 4, 4, 0, 0},
				{4, 4, 4, 4, 4, 4, 0, 0},
				{0, 0, 5, 5, 5, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};
				

	u8 purpleCar1[8][8] = {
				{6, 7, 7, 7, 6, 6, 7, 7},
				{6, 3, 7, 7, 6, 6, 7, 7},
				{6, 7, 7, 7, 7, 6, 6, 7},
				{0, 6, 7, 7, 7, 7, 7, 0},
				{0, 0, 0, 3, 3, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};

	u8 purpleCar2[8][8] = {
				{7, 7, 6, 6, 6, 7, 0, 0},
				{7, 7, 6, 6, 6, 7, 0, 0},
				{6, 7, 7, 7, 7, 7, 6, 0},
				{0, 7, 7, 7, 7, 7, 0, 0},
				{0, 0, 3, 3, 3, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0}};
				
	for (x = 0; x<8; ++x)
		for (y = 0; y<8; ++y)
		{
			setPixel(raceCarTile1,x,y,carColors[raceCar1[7-y][x]]);
			setPixel(raceCarTile2,x,y,carColors[raceCar2[7-y][x]]);
			setPixel(raceCarTile3,x,y,carColors[raceCar1[y][x]]);
			setPixel(raceCarTile4,x,y,carColors[raceCar2[y][x]]);
			
			setPixel(bullDozerTile1,x,y,carColors[bullDozer1[7-y][x]]);
			setPixel(bullDozerTile2,x,y,carColors[bullDozer2[7-y][x]]);
			setPixel(bullDozerTile3,x,y,carColors[bullDozer1[y][x]]);
			setPixel(bullDozerTile4,x,y,carColors[bullDozer2[y][x]]);
			
			setPixel(purpleCarTile1,x,y,carColors[purpleCar1[7-y][x]]);
			setPixel(purpleCarTile2,x,y,carColors[purpleCar2[7-y][x]]);
			setPixel(purpleCarTile3,x,y,carColors[purpleCar1[y][x]]);
			setPixel(purpleCarTile4,x,y,carColors[purpleCar2[y][x]]);
			
			setPixel(truckTile1,x,y,carColors[truck1[7-y][x]]);
			setPixel(truckTile2,x,y,carColors[truck2[7-y][x]]);
			setPixel(truckTile3,x,y,carColors[truck3[7-y][x]]);
			setPixel(truckTile4,x,y,carColors[truck4[7-y][x]]);
			setPixel(truckTile5,x,y,carColors[truck1[y][x]]);
			setPixel(truckTile6,x,y,carColors[truck2[y][x]]);
			setPixel(truckTile7,x,y,carColors[truck3[y][x]]);
			setPixel(truckTile8,x,y,carColors[truck4[y][x]]);
		}
	
}


