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
	View(Model);
	~View() = default;
	View(View &);
	View& operator=(View&);
	void print();// std::ostream); для тестов заменить (саша не трогай)
	void printField();
	void readMove(int&, int&);//, std::ostream);
	//void answer(); // ?? 
	Model& getModel();
//private:
	Model* model;
};

#endif

