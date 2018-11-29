#pragma once
#ifndef GAMER_H
#define GAMER_H
#include "Model.h"
#include "View.h"

class Gamer
{
public:
	virtual int fire() = 0;
	virtual void fillField() = 0; 
	//virtual Gamer() = 0;
	virtual ~Gamer() = 0;
//	virtual int checkDirection(int, int, int, Model&) = 0;
//private:
//	Model& model;
//	View& view;
};


class RandomGamer : public Gamer
{
public:
	RandomGamer(Model, View);
	~RandomGamer();
	int fire() override;
	void fillField() override;
//	int checkDirection(int, int, int, Model&) override;  //не нужна 
//private:
	Model* model;
	View* view;
};

class OptimalGamer : public Gamer
{
public:
	//int fire(Model&) override;
	//void Gamer::fillField(Model&) override;
	//int checkDirection(int, int, int, Model&) override;
};

class ConsoleGamer : public Gamer
{
public:
	ConsoleGamer(Model, View);
	~ConsoleGamer();
	int fire() override;
	void fillField() override;
//	int checkDirection(int, int, int) override;  //переименовать в мэйк и строить продолжение корабля? перенести в модель 
//private:
	Model* model;
	View* view;
};

#endif
