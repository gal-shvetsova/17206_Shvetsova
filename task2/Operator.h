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


#endif #pragma once