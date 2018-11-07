#pragma once
#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <map>
#include <stack>
#include <list>
#include <iostream>
#include "Context.h"

class Operator
{
public:
	virtual void make_operation(Context&) = 0;
	virtual ~Operator() = 0;
};


#endif #pragma once
