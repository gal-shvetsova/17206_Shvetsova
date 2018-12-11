#include "Model.h"
#include <algorithm>
#include <iostream>
#include "View.h"

int Model::checkPoint(int x, int y)  
{
	int** field;
	if (gamer == 1 && state == FILL_1)
		field = Field1;
	else if (gamer == 1 && state == FIRE_1)
		field = Field2;
	else if (gamer == 2 && state == FILL_2)
		field = Field2;
	else if (gamer == 2 && state == FIRE_2)
		field = Field1;
	else
		return 0;
	if (x < 0 || x > 9 || y < 0 || y > 9) return 0;
		if (field[x][y] || (x + 1 < 10 && field[x + 1][y]) || (x - 1 >= 0 && field[x - 1][y]) || (y - 1 >= 0 && field[x][y - 1]) || (y + 1 < 10 && field[x][y + 1]) ||
			(x + 1 < 10 && y + 1 < 10 && field[x + 1][y + 1]) || (x + 1 < 10 && y - 1 >= 0 && field[x + 1][y - 1]) || (x > 0 && y > 0 && field[x - 1][y - 1]) || (x > 0 && y < 9 && field[x - 1][y + 1]))
			return 0;
	return 1;
}


int Model::checkShip(int x, int y)
{
	int** field = gamer == 1 ? Field2 : Field1;
	if (x < 0 || x > 9 || y < 0 || y > 9  || field[x][y] == WOUND || field[x][y] == MISSED)
			return UNKNOWN;
	if (field[x][y] == SHIP)
	{
		field[x][y] = WOUND;
		return WOUND;
	}
	else if (field[x][y] == UNKNOWN)
	{
		field[x][y] = MISSED;
		return MISSED;
	}
	return UNKNOWN;
}

int Model::findShipDirection(int x, int y, int& direction)
{
	direction = setDirection(x, y);
	if (direction == -1)
		return -1;
	if (direction == UP)
		return checkShip(x - 1, y);
	if (direction == DOWN)
		return checkShip(x + 1, y);
	if (direction == RIGHT)
		return checkShip(x, y + 1);
	if (direction == LEFT)
		return checkShip(x, y - 1);
}

int Model::setDirection(int x, int y)
{
	int** field = gamer == 1 ? Field2 : Field1;
	if (x + 1 < 10 && field[x + 1][y] != 1)
		return DOWN;
	if (x - 1 >= 0 && field[x - 1][y] != 1)
		return UP;
	if (y - 1 >= 0 && field[x][y - 1] != 1)
		return LEFT;
	if (y + 1 < 10 && field[x][y + 1] != 1)
		return RIGHT;
	return -1;
}

int Model::winner()
{
	if (!ship1 && !ship2)
		return 3;
	if (!ship1)
		return 2;
	if (!ship2)
		return 1;
	return 0;
}

int ** Model::getField()
{
	if (gamer == 1)
		return Field1;
	else
		return Field2;
}

int ** Model::getEnemyField()
{
	if (gamer == 1)
		return Field2;
	if (gamer == 2)
		return Field1;
}

int Model::getGamer()
{
	return gamer;
}

void Model::setGamer()
{
	gamer = gamer == 1 ? 2 : 1;
}

void Model::setShips()
{
	if (gamer == 1) ship2--;
	if (gamer == 2) ship1--;
}

void Model::setState(states s)
{
	state = s;
}

int Model::score()
{
	int** table = gamer == 1 ? Field1 : Field2;
	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			c += table[i][j] == 3;
	}
	return c;
}

Model::Model()
{
	gamer = 1;
	Field1 = new int* [10];
	Field2 = new int* [10];
	for (int i = 0; i < 10; i++)
	{
		Field1[i] = new int [10];
		Field2[i] = new int[10];
		for (int j = 0; j < 10; j++)
		{
			Field1[i][j] = UNKNOWN;
			Field2[i][j] = UNKNOWN;
		}
	}
}


Model::~Model()
{
	for (int i = 0; i < 10; i++)
	{
		delete [] Field1[i];
		delete [] Field2[i];
	}
	delete[] Field1;
	delete[] Field2;
}

void Model::setLine(int s_x, int s_y, int e_x, int e_y)
{
	if (s_x > e_x)
		std::swap(s_x, e_x);
	int ** curField = gamer == 1 ? Field1 : Field2;
	for (int i = s_x; i <= e_x; i++)
		curField[i][s_y] = SHIP;

	if (s_y > e_y)
		std::swap(s_y, e_y);
	for (int i = s_y; i <= e_y; i++)
		curField[s_x][i] = SHIP;
}

void Model::setPoint(int x, int y, int val) 
{
	int** field = gamer == 1 ? Field2 : Field1;
	field[x][y] = val;
}
