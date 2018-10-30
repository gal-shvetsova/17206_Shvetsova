#include "Context.h"
#include "Creator.h"
#include <stack>
#include <string.h>
#include "Factory.h";
#include "Exceptions.h"

using std::string;

list<string> get_arg_l(string& buffer)
{
	list <string> args;
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
	return args;
}

void Context::compute(std::istream& in, std::ostream& out)
{
	string buffer, operation;
	OperatorCreater creator;
	while (!in.eof())
	{
		std::getline(in, buffer, '\n');
		args = get_arg_l(buffer);
		try 
		{
			if (!args.size())
			{
				throw empty_args();
			}
		}
		catch (calc_except& exc)
		{
			out << exc.what() << "\n";
			continue;
		}
		operation = args.front();
		args.pop_front();
		if (operation.front() != '#')
		{
			try
			{
			Operator*  some_oper = Factory::get_instance()->get_operator(operation);
			
				some_oper->make_operation(*this, args);
			}
			catch (calc_except& exc)
			{
				out << exc.what() << "\n";
			}
		}

	}
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