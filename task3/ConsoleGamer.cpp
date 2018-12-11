#include "Basic_Gamers.h"
#include "Gamer.h"
#include <vector>
#include <time.h>
#include <iostream>
#include "Model.h"
using std::vector;


ConsoleGamer::ConsoleGamer(Model* m, View* v)
{
	model = m;
	view = v;
}

ConsoleGamer::~ConsoleGamer()
{
	model = nullptr;
	view = nullptr;
}


vector<int> ConsoleGamer::checkDirection(int x, int y, int size)  
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



int ConsoleGamer::fire()
{
	int x, y, check = 0;
	while (!check)
	{
		view->readMove(x, y);
		check = model->checkShip(x, y);
		view->answer(check);
	}
	return check;
}

void ConsoleGamer::fillField()
{
	int count = 0, pol = 0, x, y;
	int size[10] = { 0,0,0,0,1,1,1,2,2,3 };
	int i, check;
	vector <int> dir;
	while (count < 10)
	{
		view->print();
		view->readMove(x, y);
		dir = checkDirection(x, y, size[count]);
		pol = view->turn(size[count]);
		check = 0;
		for (i = 0; i < dir.size() && !check; i++)
			check = pol == dir[i];
		if (check)
		{
			if (pol == DOWN)
				model->setLine(x, y, x + size[count], y);
			if (pol == UP)
				model->setLine(x, y, x - size[count], y);
			if (pol == RIGHT)
				model->setLine(x, y, x, y + size[count]);
			if (pol == LEFT)
				model->setLine(x, y, x, y - size[count]);
			count++;
		}
		else
			view->printError();
	}
	model->setGamer();
}