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

void writeOutCar(u32 graphic1[], u32 graphic2[], u8 tile1, u8 tile2, u8 tile3, u8 tile4)
{
	u8 carColors[8] = {BLACK,PURPLE,RED,YELLOW,GREY,GREEN,CYAN,PURPLE};
	
	u32 temp[8];
	mapArrayToTile(graphic1, carColors, tile3);
	mapArrayToTile(graphic2, carColors, tile4);
	flip(graphic1, temp, 0, 1);
	mapArrayToTile(temp, carColors, tile1);
	flip(graphic2, temp, 0, 1);
	mapArrayToTile(temp, carColors, tile2);
}

void outputCarTiles()
{
	int x, y;

	u32 raceCar1[8] = {
				0x03232323,
				0x11111133,
				0x00333333,
				0x00010000,
				0x02222200,
				0x02222200,
				0x02222200,
				0x00000000};

	u32 raceCar2[8] = {
				0x31113333,
				0x11133330,
				0x33333300,
				0x00010000,
				0x02222200,
				0x02222200,
				0x00000000,
				0x00000000};

	u32 bullDozer1[8] = {
				0x04455545,
				0x04444455,
				0x00444444,
				0x00500050,
				0x04242424,
				0x04242424,
				0x00000000,
				0x00000000};

	u32 bullDozer2[8] = {
				0x44004200,
				0x45004440,
				0x44004200,
				0x05554440,
				0x00004200,
				0x00004440,
				0x00000000,
				0x00000000};	
	
	u32 truck1[8] = {
				0x00024444,
				0x00024444,
				0x00024444,
				0x00002444,
				0x00000055,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 truck2[8] = {
				0x42444444,
				0x42444444,
				0x40444444,
				0x40444444,
				0x50055500,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 truck3[8] = {
				0x44444444,
				0x44444444,
				0x44444444,
				0x44444444,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 truck4[8] = {
				0x44444400,
				0x44444400,
				0x44444400,
				0x44444400,
				0x00555000,
				0x00000000,
				0x00000000,
				0x00000000};
				

	u32 purpleCar1[8] = {
				0x67776677,
				0x63776677,
				0x67777667,
				0x06777770,
				0x00033000,
				0x00000000,
				0x00000000,
				0x00000000};

	u32 purpleCar2[8] = {
				0x77666700,
				0x77666700,
				0x67777760,
				0x07777700,
				0x00333000,
				0x00000000,
				0x00000000,
				0x00000000};
	
	writeOutCar(raceCar1,raceCar2,raceCarTile1,raceCarTile2,raceCarTile3,raceCarTile4);
	writeOutCar(bullDozer1,bullDozer2,bullDozerTile1,bullDozerTile2,bullDozerTile3,bullDozerTile4);
	writeOutCar(purpleCar1,purpleCar2,purpleCarTile1,purpleCarTile2,purpleCarTile3,purpleCarTile4);
	writeOutCar(truck1,truck2,truckTile1,truckTile2,truckTile5,truckTile6);
	writeOutCar(truck3,truck4,truckTile3,truckTile4,truckTile7,truckTile8);
	
	
	
}


