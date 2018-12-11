#include "Basic_Gamers.h"
#include "Gamer.h"
#include <vector>
#include <time.h>
#include <iostream>
#include "Model.h"
using std::vector;

OptimalGamer::OptimalGamer(Model * m, View * v)
{
	model = m;
	view = v;
	last_x = -1;
	last_y = -1;
	strategy_x = 1;
	strategy_y = 0;
	last_result = -1;
	sides = 0;
}

OptimalGamer::~OptimalGamer()
{
	model = nullptr;
	view = nullptr;
}


vector<int> OptimalGamer::checkDirection(int x, int y, int size)  
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



void OptimalGamer::updateXY(int x, int y)
{
	if (last_result == UP)
		last_x = x - 1;
	if (last_result == DOWN)
		last_x = x + 1;
	if (last_result == RIGHT)
		last_y = y + 1;
	if (last_result == LEFT)
		last_y = y - 1;
}

void OptimalGamer::switchDirection()
{
	if (last_result == UP) last_result = DOWN;
	else if (last_result == DOWN) last_result = UP;
	if (last_result == RIGHT) last_result = LEFT;
	else if (last_result == LEFT) last_result = RIGHT;
}

// mark cells that don't have a ship. if direction is undefined fills only diagonal cells //
void OptimalGamer::optimize(int x, int y, int dir)
{
	int** field = model->getEnemyField();
	if (x + 1 < 10 && y + 1 < 10)
		model->setPoint(x + 1, y + 1, MISSED);
	if (x + 1 < 10 && y - 1 > -1)
		model->setPoint(x + 1, y - 1, MISSED);
	if (x - 1 > -1 && y + 1 < 10)
		model->setPoint(x - 1, y + 1, MISSED);
	if (x - 1 > -1 && y - 1 > -1)
		model->setPoint(x - 1, y - 1, MISSED);
	if (dir < 0)	return;
	if (dir == UP || dir == DOWN)
	{
		if (y + 1 < 10)
			model->setPoint(x, y + 1, MISSED);
		if (y - 1 > -1)
			model->setPoint(x, y - 1, MISSED);
	}
	if (dir == LEFT || dir == RIGHT)
	{
		if (x + 1 < 10)
			model->setPoint(x + 1, y, MISSED);
		if (x - 1 > -1)
			model->setPoint(x - 1, y, MISSED);
	}
}

void OptimalGamer::updateStrategicXY()
{
	if (strategy_x == 8 && strategy_y == 9)
	{
		strategy_x = 0;
		strategy_y = 0;
	}
	if (strategy_y + 1 < 10 && strategy_x - 1 >= 0)
	{
		strategy_x--;
		strategy_y++;
		return;
	}
	if (strategy_x - 1 < 0)
	{
		std::swap(strategy_x, strategy_y);
		strategy_x += 2;
		return;
	}
	if (strategy_y + 1 > 9)
	{
		std::swap(strategy_x, strategy_y);
		strategy_y += 2;
		return;
	}


}

int checkSingle(int x, int y, int** field)
{
	if (x + 1 < 10 && field[x + 1][y] == 1 && x - 1 >= 0 && field[x - 1][y] == 1 && y - 1 >= 0 && field[x][y - 1] == 1 && y + 1 < 10 && field[x][y + 1] == 1)
		return MISSED;
	else
		return 0;
}

int OptimalGamer::fire()
{

	int x, y, check_s = 0, check_d = 0, check_f = 0, direction = 0;
	//  progress on strategy: if the last move did not get and direction is undefined
	while (1) {
		check_s = 0, check_d = 0, check_f = 0, direction = 0;
		if (last_result < 0)
		{
			while (!check_s) //until we get to the cage that hasn't been shot yet
			{
				x = strategy_x;
				y = strategy_y;
				check_s = model->checkShip(x, y);
				if (check_s == WOUND)
				{
					model->setShips();
					optimize(x, y, -1);
					last_result = 0;
					last_x = x;
					last_y = y;
					view->printField();
				}
				if (!check_s)
					updateStrategicXY();
			}
		}
		else
			check_s = WOUND;

		if (check_s == MISSED)
		{
			view->printField();
			updateStrategicXY();
			return MISSED;
		}
		//  the determination of the direction: if ship wounded but unknown direction //

		while (check_s == WOUND && check_d != MISSED && !last_result)
		{
			x = last_x;
			y = last_y;
			check_d = model->findShipDirection(x, y, direction); //won't change coordinates
			if (check_d < 0)
			{
				updateStrategicXY();
				last_result = -1;
				sides = 0;
				view->printField();
				return MISSED;
			}
			if (check_d == WOUND)
			{
				last_result = direction;
				optimize(x, y, last_result);
				updateXY(x, y);  //change coordinates and write it to last
				x = last_x;
				y = last_y;
				optimize(x, y, last_result);
				model->setShips();
				view->printField();
			}
		}

		if (check_d == MISSED)
		{
			view->printField();
			return MISSED;
		}

		//  shooting by direction //

		while (last_result && check_f != MISSED && sides != 2)
		{
			x = last_x;
			y = last_y;
			updateXY(x, y);
			x = last_x;
			y = last_y;
			if (x < 10 && y < 10 && y > -1 && x > -1)
				check_f = model->checkShip(x, y);
			else
				check_f = -1;
			view->printField();
			if ((check_f == MISSED || check_f == -1) && sides != 2) 
			{
				switchDirection();
				last_x = x;
				last_y = y;
				sides++;
			}
			if (check_f == WOUND)
			{
				last_x = x;
				last_y = y;
				optimize(x, y, last_result);
				model->setShips();
				view->printField();
			}
		}
		if (check_f == MISSED)
		{
			view->printField();
			return MISSED;
		}
		if (sides == 2)
		{
			updateStrategicXY();
			last_result = -1;
			sides = 0;
		}
	}
	view->printField();
	return WOUND;
}

bool checkDir(vector<int> dir, int pol) 
{
	int check = 0;
	for (int i = 0; i < dir.size() && !check; i++)
		check = pol == dir[i];
	return check;
}
void OptimalGamer::fillField()
{
	int count = 9, pol = 0, x, y; 
	vector <int> dir;
	int size[10] = { 0,0,0,0,1,1,1,2,2,3 };
	x = rand() % 2;
	x = 0 ? 0 : 9;
	y = 0;
	for (int i = 0; i < 3; i++)
	{
		dir = checkDirection(x, y, size[count]);
		if (checkDir(dir, RIGHT))
		{
			model->setLine(x, y, x, y + size[count]);  
			y += size[count] + 2;
			count--;
		}
		else
		{
			y = 9;
			pol = dir[rand() % dir.size()];
			if (pol == UP)
			{
				model->setLine(x, y, x - size[count], y);
				x -= size[count] + 2;
			}
			if (pol == DOWN)
			{
				model->setLine(x, y, x + size[count], y);
				x += size[count] + 2;
			}
			count--;
		}
		view->print();
	}
	pol = rand() % 3;
	if (pol == 2)
	{
		x = 9 - x;
		y = 0;
	}
	else 
	{
		if (!y)
		{
			if (!x)
				y = 2;
			else y = 0;
		}
		if (y)
		{
			if (!x)
				y = 7;
			else y = 9;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		dir = checkDirection(x, y, size[count]);
		if (checkDir(dir, UP))
		{
			model->setLine(x, y, x - size[count], y); 
			x -= size[count] + 2;
			count--;
		}
		else if (checkDir(dir, DOWN))
		{
			model->setLine(x, y, x + size[count], y); 
			x += size[count] + 2;
			count--;
		}
		else
		{
			x = 9;
			if (!dir.size())
			{
				y = 9 - y;
				x = 9 - x;
			}
			dir = checkDirection(x, y, size[count]);
			pol = dir[rand() % dir.size()];
			if (pol == RIGHT)
				model->setLine(x, y, x, y + size[count]);
			if (pol == LEFT)
				model->setLine(x, y, x, y - size[count]);
			y += size[count] + 2;
			count--;
		}
		view->print();
	}
	while (count > -1)
	{
		pol = 0;
		x = rand() % 10;
		y = rand() % 10;
		dir = checkDirection(x, y, size[count]);
		if (dir.size())
		{
			model->setLine(x, y, x, y);
			count--;
		}
	}
}

