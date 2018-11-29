#include "Basic_Gamers.h"
#include <vector>
#include <time.h>
#include <vector>
#include <iostream>
#include "Model.h"
using std::vector;

RandomGamer::RandomGamer(Model m, View  v)
{
	model = new Model(m);
	view = new View(m);
}

RandomGamer::~RandomGamer()
{
	view = nullptr;
	model = nullptr;
}

int RandomGamer::fire()
{
	int x, y, check = 0;
	int** field = model->getField();
	while (!check)
	{
		x = rand() % 10;
		y = rand() % 10;
		check = checkShip(x, y, field);
		if (check == 1) model->setShips();
	}
	model->setGamer();
	view->printField();
	return check;
}

int checkDirection(int x, int y, int size, int** field)  //придумать как покороче сделать утилитарное?
{
	vector <int> direct;
	int i = 0;
	bool check = true;
	while (i <= size && check)
	{
		check = checkPoint(x + i, y, field);
		if (x + i > 9) check = false;
		i++;
	}
	if (check) direct.push_back(UP);
	i = 0;
	check = true;
	while (i <= size && check)
	{
		check = checkPoint(x - i, y, field);
		if (x - i < 0) check = false;
		i++;
	}
	if (check) direct.push_back(DOWN);
	i = 0;
	check = true;
	while (i <= size && check)
	{
		check = checkPoint(x, y + i, field);
		if (y + i > 9) check = false;
		i++;
	}
	if (check) direct.push_back(RIGHT);
	i = 0;
	check = true;
	while (i <= size && check)
	{
		check = checkPoint(x, y - i, field);
		if (y - i < 0) check = false;
		i++;
	}
	if (check) direct.push_back(LEFT);
	i = 0;
	check = true;
	if (!direct.size())
		return 0;
	else
		return direct[rand() % direct.size()];
}

void RandomGamer::fillField()
{
	int count = 0, pol = 0, x, y ;
	int size[10] = { 0,0,0,0,1,1,1,2,2,3 };
	while (count < 10)
	{
		pol = 0;
		x = rand() % 10;
		y = rand() % 10;
		pol = checkDirection(x, y, size[count], model->getField());
		if (pol != 0)
		{
			if (pol == UP)
				model->setLine(x, y, x + size[count], y);
			if (pol == DOWN)
				model->setLine(x, y, x - size[count], y);
			if (pol == RIGHT)
				model->setLine(x, y, x, y + size[count]);
			if (pol == LEFT)
				model->setLine(x, y, x, y - size[count]);
			count++;
		}
	}
	model->setGamer();
}

ConsoleGamer::ConsoleGamer(Model m, View v)
{
	model = new Model(m);
	view = new View(m);
}

ConsoleGamer::~ConsoleGamer()
{
	view = nullptr;
	model = nullptr;
}

int ConsoleGamer::fire()
{
	int x, y, check = 0;
	int** field = model->getField();
	while (!check)
	{
		view->readMove(x, y);
		check = checkShip(x, y, field);
		if (!check) std::cout << ""; //придумать вывод
	}
	return check;
}

void ConsoleGamer::fillField()
{
	int count = 20, pol = 0, x, y;
	while (count)
	{
		pol = 0;
		view->readMove(x, y);
		pol = checkDirection(x, y, 0, model->getField());
		if (pol != 0) {
			model->setLine(x, y, x, y);
			count--;
			view->print();  //??
		}
		else
			std::cout << "Wrong x, y\n";
		
	}
	model->setGamer();
}

