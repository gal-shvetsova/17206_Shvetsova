#ifndef BASICOP_H
#define BASICOP_H

#include "Operator.h"

class Add : public Operator
{
public:
	void make_operation(Context&) override;
	~Add() override {};
};

class Subtract : public Operator
{
public:
	void make_operation(Context&) override;
};

class Multiplicate : public Operator
{
public:
	void make_operation(Context&) override;
};

class Division : public Operator
{
public:
	void make_operation(Context&) override;
};

class Sqrt : public Operator
{
public:
	void make_operation(Context&) override;
};

class Pop : public Operator
{
public:
	void make_operation(Context&) override;
};

class Push : public Operator
{
public:
	void make_operation(Context&) override;
};

class Print : public Operator
{
public:
	void make_operation(Context&) override;
};

class Define : public Operator
{
public:
	void make_operation(Context&) override;
};

#endif // !