#pragma once
#ifndef  CREATOR_H
#define CREATOR_H

#include <map>
#include "Operator.h"

class OperatorCreater
{
private:
public:
	virtual Operator* create() { return NULL; };
};

class AddCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class SubCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class MulCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class DivCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class SqrtCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class PrintCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class PopCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class PushCreator : public OperatorCreater
{
public:
	Operator* create() override;
};

class DefineCreator : public OperatorCreater
{
public:
	Operator* create() override;
};


#endif // ! CREATOR_H
#pragma once
