#pragma once
#ifndef GAMER_H
#define GAMER_H
#include "Model.h"
#include "View.h"
#include <vector>

using std::vector;

class Gamer
{
public:
	virtual int fire() = 0;
	virtual void fillField() = 0; 
	virtual vector<int> checkDirection(int x, int y, int size) = 0;
};

#endif
