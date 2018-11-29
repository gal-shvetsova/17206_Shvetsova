#include "Model.h"
#include <algorithm>
#include <iostream>

int checkPoint(int x, int y, int** field)  //условия норм сделать и передавать в функцию таблицу ассерты убрать из модели и передвать поле
{
		if (field[x][y] || (x + 1 < 10 && field[x + 1][y]) || (x - 1 >= 0 && field[x - 1][y]) || (y - 1 >= 0 && field[x][y - 1]) || (y + 1 < 10 && field[x][y + 1]) ||
			(x + 1 < 10 && y + 1 < 10 && field[x + 1][y + 1]) || (x + 1 < 10 && y - 1 >= 0 && field[x + 1][y - 1]) || (x > 0 && y > 0 && field[x - 1][y - 1]) || (x > 0 && y < 9 && field[x - 1][y + 1]))
			return 0;
	return 1;
}

int checkKill(int x, int y, int** field) //? 
{
	int i, k;
	if (x < 8)
		i = (field[x + 1][y] >= SHIP);
	if (x > 0)
		i = -(field[x - 1][y] >= SHIP);
	if (y < 8)
		k = (field[x][y + 1] >= SHIP);
	if (y > 0)
		k = -(field[x + 1][y] >= SHIP);
	while (field[x][y] > SHIP)
	{
		x += i;
		y += k;
		if (field[x][y] == SHIP)
		return 0;
	}
	return 1;
}

int checkShip(int x, int y, int** field)
{
	if (field[x][y] == WOUND || field[x][y] == MISSED)
			return 0;
	if (field[x][y] == SHIP)
	{
		field[x][y] = WOUND;
		return 2;
	}
	else if (field[x][y] == UNKNOWN)
	{
		field[x][y] = MISSED;
		return 1;
	}
	return 0;
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

Model::Model (Model & m)
{
	gamer = 1;
	Field1 = m.getField();
	Field2 = m.getEnemyField();
}

Model & Model::operator=(Model m)
{
	if (this != &m) {
		for (int i = 0; i < 10; i++)
			delete Field1[i];
		delete[] Field1;
		for (int i = 0; i < 10; i++)
			delete Field2[i];
		delete[] Field2;
		Field1 =  new int*[10];
		Field2 = new int*[10];
		for (int i = 0; i < 10; i++) {
			Field1[i] = new int;
			Field2[i] = new int;
		}
		Field1 = getField();
		Field2 = getEnemyField();
	}
	return (*this);
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
		delete Field1[i];
		delete Field2[i];
	}
	delete[] Field1;
	delete[] Field2;
}

void Model::setLine(int s_x, int s_y, int e_x, int e_y)
{
	if (s_x > e_x)
		std::swap(s_x, e_x);
	if (gamer == 1)
	{
		for (int i = s_x; i <= e_x; i++)
			Field1[i][s_y] = SHIP;

		if (s_y > e_y)
			std::swap(s_y, e_y);
		for (int i = s_y; i <= e_y; i++)
			Field1[s_x][i] = SHIP;
	}
	if (gamer == 2)
	{
		for (int i = s_x; i <= e_x; i++)
			Field2[i][s_y] = SHIP;

		if (s_y > e_y)
			std::swap(s_y, e_y);
		for (int i = s_y; i <= e_y; i++)
			Field2[s_x][i] = SHIP;
	}
}
