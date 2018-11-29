#pragma once
#ifndef MODEL_H
#define MODEL_H
//#include "Gamer.h"
#define SHIP 2
#define WOUND 3
#define KILL 4
#define UNKNOWN 0
#define MISSED 1

int checkShip(int x, int y, int** field);
int checkKill(int x, int y, int** field);
int checkPoint(int x, int y, int** field);

class Model
{
public:

	Model();// добить до правила пяти
	Model (Model &);
	Model & operator=(Model);  
	~Model();
	void setLine(int, int, int, int); 
	int winner();
	int** getField();
	int** getEnemyField();
	int getGamer();
	void setGamer();
	void setShips();
private:
	int gamer = 1;
	int ship1 = 20;
	int ship2 = 20;
	int** Field1;
	int** Field2;
};

#endif

