#pragma once
#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include "Model.h"
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

class View
{
public:
	View(Model*);
	View() = default;
	~View() = default;
	View(View*);
	View& operator=(View&);
	void print();
	void printField();
	void readMove(int&, int&);
	void printGamer();
	void printError();
	int turn(int);
	void printRound(int);
	void printWinner(int);
	void answer(int); 
private:
	Model* model;
};

#endif

