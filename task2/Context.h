#pragma once
#pragma once
#ifndef CONTEXT_H
#define CONTEXT_H
#include <stack>
#include <map>
#include <string>
#include <iostream>
#include <list>
#include <float.h>

using std::list;
using std::stack;
using std::map;
using std::string;

list<string> get_arg_l(string& buffer);

class Context
{
public:
	void compute(std::istream&, std::ostream&);

	//work with stack
	double pop_arg();
	void push_arg(double);
	double top_arg(); 
	double size_arg();

	// work with map
	double find_var(string&);
	void add_var(string, double);
	bool is_empty_var();

private:
	stack<double> arg_stack;
	map<string, double> variables;
	list<string> args;
	int stack_size = 0;
};

#endif
