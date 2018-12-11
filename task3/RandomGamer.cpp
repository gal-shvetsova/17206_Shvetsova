#include "Basic_Gamers.h"
#include "Gamer.h"
#include <vector>
#include <time.h>
#include <iostream>
#include "Model.h"
using std::vector;

RandomGamer::RandomGamer(Model* m, View*  v)
{
	model = m;
	view = v;
}

RandomGamer::~RandomGamer()
{
	model = nullptr;
	view = nullptr;
}


vector<int> RandomGamer::checkDirection(int x, int y, int size) 
{
	vector <int> direct;
	int i = 0;
	bool check = true;
	while (i <= size && check)
	{
		check = model->checkPoint(x + i, y);
		if (x + i > 9) check = false;
		i++;
	}
	if (check) direct.push_back(DOWN);
	i = 0;
	check = true;
	while (i <= size && check)
	{
		check = model->checkPoint(x - i, y);
		if (x - i < 0) check = false;
		i++;
	}
	if (check) direct.push_back(UP);
	i = 0;
	check = true;
	while (i <= size && check)
	{
		check = model->checkPoint(x, y + i);
		if (y + i > 9) check = false;
		i++;
	}
	if (check) direct.push_back(RIGHT);
	i = 0;
	check = true;
	while (i <= size && check)
	{
		check = model->checkPoint(x, y - i);
		if (y - i < 0) check = false;
		i++;
	}
	if (check) direct.push_back(LEFT);
	i = 0;
	check = true;
	return direct;
}



int RandomGamer::fire()
{
	int x, y, check = 0;
	while (check != MISSED)
	{
		x = rand() % 10;
		y = rand() % 10;
		check = model->checkShip(x, y);
		if (check == WOUND)
			model->setShips();
	}
	view->printField();
	return check;
}

void RandomGamer::fillField()
{
	int count = 9, pol = 0, x, y;
	vector <int> dir;
	int size[10] = { 0,0,0,0,1,1,1,2,2,3 };
	while (count > -1)
	{
		pol = 0;
		x = rand() % 10;
		y = rand() % 10;
		dir = checkDirection(x, y, size[count]);
		if (dir.size())
			pol = dir[rand() % dir.size()];
		if (pol != 0)
		{
			if (pol == UP)
				model->setLine(x, y, x - size[count], y);
			if (pol == DOWN)
				model->setLine(x, y, x + size[count], y);
			if (pol == RIGHT)
				model->setLine(x, y, x, y + size[count]);
			if (pol == LEFT)
				model->setLine(x, y, x, y - size[count]);
			count--;
		}
	}
}