#include "View.h"

using std::cout;
using std::cin;

View::View(Model* m)
{
	model = m;
}

View::View(View * v)
{
	model = v->model;
}

View & View::operator=(View & v)
{
	if (this != &v)
	{
		model = v.model;
	}
	return *this;
}

void View::print()
{
	int** field = model->getField();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (field[i][j] == SHIP) 
				cout << "|#" << " ";
			if (field[i][j] == UNKNOWN)
				cout << "|  " ;
		}
		cout << "|\n";
	}
	cout << "\n";
}

void View::printField()
{
	int** field = model->getEnemyField();
	cout << "Gamer: " << model->getGamer() << "\n";
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (field[i][j] == WOUND)
				cout << "|#";
			else if (field[i][j] == SHIP || field[i][j] == UNKNOWN)
				cout << "|.";
			else if (field[i][j] == MISSED)
				cout << "|+";
		}
		cout << "|\n";
	}
	cout << "\n";
}

void View::readMove(int& x, int& y) 
{
	cout << "Enter x: ";
	cin >> x;
	cout << "Enter y: ";
	cin >> y;
}

void View::printGamer()
{
	cout << model->getGamer() << "\n";
}

void View::printError()
{
	cout << "Wrong x, y\n";
}

int View::turn(int ship)
{
	int pol;
	cout << "Ship: " << ship + 1 << "\n";
	cout << "Enter direction: 1 - UP 2 - DOWN 3 - RIGHT 4 - LEFT : ";
	cin >> pol;
	return pol;
}

void View::printRound(int round)
{
	cout << "Round : " << round << "\n";
}

void View::printWinner(int winner)
{
	if (winner != 3)
		cout << "Gamer " << winner << " won!";
	else
		cout << "Draw.";

	cout << " " << model->score();
	model->setGamer();
	cout << " " << model->score();
	cin >> winner;

}

void View::answer(int check)
{
	if (check == UNKNOWN)
		cout << "You already shot here\n";
	if (check == MISSED)
		cout << "You missed\n";
	if (check == WOUND)
		cout << "You wound the ship\n";
}

