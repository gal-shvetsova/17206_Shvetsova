#pragma once
#ifndef MODEL_H
#define MODEL_H
#define SHIP 2
#define WOUND 3
#define KILL 4
#define UNKNOWN 0
#define MISSED 1

enum states { FILL_1 = 1, FILL_2, FIRE_1, FIRE_2 };

class Model
{
public:

	Model();
	Model (const Model &) = delete;
	Model &operator=(const Model &) = delete;  
	~Model();
	void setLine(int, int, int, int); 
	int checkShip(int x, int y);
	int checkPoint(int x, int y);
	void setPoint(int, int, int);
	int setDirection(int x, int y);
	int findShipDirection(int x, int y, int& direction);
	int winner();
	int** getField();
	int** getEnemyField();
	int getGamer();
	void setGamer();
	void setShips();
	void setState(states);
	int score();
private:
	int state;
	int gamer = 1;
	int ship1 = 20;
	int ship2 = 20;
	int** Field1;
	int** Field2;
};

#endif

