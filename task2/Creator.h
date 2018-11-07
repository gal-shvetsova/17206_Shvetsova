#pragma once
#ifndef  CREATOR_H
#define CREATOR_H

#include <map>
#include "BasicOp.h"

class OperatorCreater
{
private:
public:
	virtual Operator* create() { return NULL; };
};

class AddCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Add* add = new Add;
		return add;
	}
};

class SubCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Subtract* sub = new Subtract;
		return sub;
	}
};

class MulCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Multiplicate* mul = new Multiplicate;
		return mul;
	}
};

class DivCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Division* div = new Division;
		return div;
	}
};

class SqrtCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Sqrt* sqrt = new Sqrt;
		return sqrt;
	}
};

class PrintCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Print* print = new Print;
		return print;
	}
};

class PopCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Pop* pop = new Pop;
		return pop;
	}
};

class PushCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Push* push = new Push;
		return push;
	}
};

class DefineCreator : public OperatorCreater
{
public:
	Operator* create() override
	{
		Define* define = new Define;
		return define;
	}
};


#endif // ! CREATOR_H
#pragma once
