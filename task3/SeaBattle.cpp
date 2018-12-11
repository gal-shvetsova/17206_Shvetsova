#include "SeaBattle.h"
#include "Basic_Gamers.h"

Gamer* fabric(Model* model, View* view, const std::string &type)
{
	if (type == "console")
	{
		ConsoleGamer* gamer = new ConsoleGamer(model, view);
		return gamer;
	}
	if (type == "optimal")
	{
		OptimalGamer* gamer = new OptimalGamer(model, view);
		return gamer;
	}
	else
	{
		RandomGamer* gamer = new RandomGamer(model, view);
		return gamer;
	}
}

void SeaBattle::Play(const std::string &firstType, const std::string &secondType, const int rounds)
{
	for (int round = 1; round <= rounds; round++)
	{
		Model*  model = new Model;
		View* view = new View(model);
		view->printRound(round);
		Gamer* gamer1 = fabric(model, view, firstType);
		Gamer* gamer2 = fabric(model, view, "optimal");
		model->setState(FILL_1);
		gamer1->fillField();
		model->setGamer();
		model->setState(FILL_2);
		gamer2->fillField();
		view->print();
		model->setGamer();
		view->print();
		model->setGamer();
		int winner = 0;
		while (!winner)
		{
			model->setState(FIRE_1);
			gamer2->fire();
			model->setGamer();
			model->setState(FIRE_2);
			gamer1->fire();
			model->setGamer();
			winner = model->winner();
		}
		view->printWinner(winner);
		delete gamer1;
		delete gamer2;
		delete model;
		delete view;
	}
}
