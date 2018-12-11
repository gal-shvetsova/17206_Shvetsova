#ifndef BASIC_GAMER_H
#define BASIC_GAMER_H
#include "Gamer.h"

class RandomGamer : public Gamer
{
public:
	RandomGamer(Model*, View*);
	~RandomGamer();
	int fire() override;
	void fillField() override;
	vector<int> checkDirection(int x, int y, int size) override;
private:
	Model* model;
	View* view;
};

class OptimalGamer : public Gamer
{
public:
	OptimalGamer(Model*, View*);
	~OptimalGamer();
	int fire() override;
	void fillField() override;
	vector<int> checkDirection(int x, int y, int size);
private:
	void updateXY(int, int);
	void updateStrategicXY();
	void switchDirection();
	void optimize(int, int, int);
	Model* model;
	View* view;
	int sides;
	int last_x;
	int last_y;
	int strategy_x, strategy_y;
	int last_result;
};

class ConsoleGamer : public Gamer
{
public:
	ConsoleGamer(Model*, View*);
	~ConsoleGamer();
	int fire() override;
	void fillField() override;
	vector<int> checkDirection(int x, int y, int size);
private:
	Model* model;
	View* view;
};


#endif