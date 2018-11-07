#include "Context.h"
#include "Creator.h"
#include <stack>
#include <string.h>
#include "Factory.h"
#include "Exceptions.h"

using std::string;

void Context::get_arg_l(string& buffer)
{
	int j = 0;
	for (int i = 0; i < buffer.length(); i++)
	{
		if (buffer[i] == ' ')
		{
			args.push_back(buffer.substr(j, i - j));
			j = i + 1;
		}

	}
	if (j < buffer.length())
		args.push_back(buffer.substr(j, buffer.length() - j));
}

int Context::size_l()
{
	return args.size();
}

std::string Context::front_l()
{
	return args.front();
}

std::string& Context::back_l()
{
	return args.back();
}

void Context::pop_back_l()
{
	args.pop_back();
}

void Context::pop_front_l()
{
	args.pop_front();
}

double Context::pop_arg()
{
	if (!size_arg())
		throw empty_stack();
	double arg = arg_stack.top();
	arg_stack.pop();
	stack_size--;
	return arg;
}

void Context::push_arg(double arg)
{
	arg_stack.push(arg);
	stack_size++;
}

double Context::top_arg()
{
	if (!size_arg())
		throw empty_stack();
	return arg_stack.top();
}

double Context::size_arg()
{
	return stack_size;
}

bool Context::is_empty_var()
{
	return variables.empty();
}

double Context::find_var(string& name)
{
	if (!variables.size())
		throw nodefinition();
	if (variables.find(name) != variables.end())
		return variables[name];
	return DBL_MIN; 
}

void Context::add_var(string name, double value)
{
	variables[name] = value;
}