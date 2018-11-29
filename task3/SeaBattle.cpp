#include "SeaBattle.h"


SeaBattle::SeaBattle()
{
}


SeaBattle::~SeaBattle()
{
}

int count(int** table)
{
	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			c += table[i][j] == 3;
	}
	return c;
}

void SeaBattle::Play()
{
	Model model;
	View view(model);
	RandomGamer gamer1(model, view);
	ConsoleGamer gamer2(model, view);
	gamer1.fillField();
	gamer2.fillField();
	view.print();
	model.setGamer();
	view.print();
	int winner = 0;
	while (!winner)
	{
		gamer1.fire();
		winner = model.winner();

	}
	if (winner != 3)
		std::cout << "Gamer " << winner << " won!";
	else
		std::cout << "Draw.";
	std::cout << " " << count(model.getField());
	model.setGamer();
	std::cout << " " << count(model.getField());
}
