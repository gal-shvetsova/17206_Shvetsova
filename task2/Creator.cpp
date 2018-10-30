#include "Operator.h"
#include "Creator.h"

Operator * AddCreator::create()
{
	Add* add = new Add;
	return add;
}

Operator * SubCreator::create()
{
	Subtract* sub = new Subtract;
	return sub;
}

Operator * MulCreator::create()
{
	Multiplicate* mul = new Multiplicate;
	return mul;
}

Operator * DivCreator::create()
{
	Division* div = new Division;
	return div;
}

Operator * SqrtCreator::create()
{
	Sqrt* sqrt = new Sqrt;
	return sqrt;
}


Operator * PopCreator::create()
{
	Pop* pop = new Pop;
	return pop;
}

Operator * PushCreator::create()
{
	Push* push = new Push;
	return push;
}

Operator * PrintCreator::create()
{
	Print* print = new Print;
	return print;
}

Operator * DefineCreator::create()
{
	Define* define = new Define;
	return define;
}


