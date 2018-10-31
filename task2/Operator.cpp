#include "Operator.h"
#include <math.h>
#include "Exceptions.h"
#include <string>
#include "Factory.h"
#include "Creator.h"

namespace {
	bool add_commands() noexcept
	{
		AddCreator* add = new AddCreator;
		Factory::get_instance()->make_command("+", add);
		SubCreator* sub = new SubCreator;
		Factory::get_instance()->make_command("-", sub);
		MulCreator* mul = new MulCreator;
		Factory::get_instance()->make_command("*", mul);
		DivCreator* div = new DivCreator;
		Factory::get_instance()->make_command("/", div);
		SqrtCreator* sqrt = new SqrtCreator;
		Factory::get_instance()->make_command("SQRT", sqrt);
		PopCreator* pop = new PopCreator;
		Factory::get_instance()->make_command("POP", pop);
		PushCreator* push = new PushCreator;
		Factory::get_instance()->make_command("PUSH", push);
		PrintCreator* print = new PrintCreator;
		Factory::get_instance()->make_command("PRINT", print);
		DefineCreator* define = new DefineCreator;
		Factory::get_instance()->make_command("DEFINE", define);
		return 1;
	}

	bool fake = add_commands();
}

bool check(std::string buffer)
{
	int i = 0;
	while (buffer[i] >= 48 && buffer[i] <= 57 || buffer[i] == '.')
		i++;
	if (i == buffer.length() - 1)
		return 1;
	return 0;
}

void Add::make_operation(Context& context, list<string>& args)
{
	double arg[2];
	if (args.size() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && args.size()) 
	{
		arg[counter] = context.find_var(args.back());
		if (arg[counter] == DBL_MIN)
		{
			if (!check(args.back()))
				throw invalid_arg();
			arg[counter] = std::stod(args.back());
		}
		args.pop_back();
		counter++;
	}
	while (counter != 2)
	{
		arg[counter] = context.pop_arg();
		counter++;
	}
	context.push_arg(arg[0] + arg[1]);
}

void Subtract::make_operation(Context& context, list<string>& args)
{
	double arg[2];
	if (args.size() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && args.size()) 
	{
		arg[counter] = context.find_var(args.back());
		if (arg[counter] == DBL_MIN)
		{
			if (!check(args.back()))
				throw invalid_arg();
			arg[counter] = std::stod(args.back());
		}
		args.pop_back();
		counter++;
	}
	while (counter != 2)
	{
		arg[counter] = context.pop_arg();
		counter++;
	}
	context.push_arg(arg[1] - arg[0]);
}

void Multiplicate::make_operation(Context& context, list<string>& args)
{
	double arg[2];
	if (args.size() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && args.size()) 
	{
		arg[counter] = context.find_var(args.back());
		if (arg[counter] == DBL_MIN)
		{
			if (!check(args.back()))
				throw invalid_arg();
			arg[counter] = std::stod(args.back());
		}
		args.pop_back();
		counter++;
	}
	while (counter != 2)
	{
		arg[counter] = context.pop_arg();
		counter++;
	}
	context.push_arg(arg[0] * arg[1]);
}

void Division::make_operation(Context& context, list<string>& args)
{
	double arg[2];
	if (args.size() + context.size_arg() < 2)
		throw empty_args();
	int counter = 0;
	while (counter != 2 && args.size()) 
	{
		arg[counter] = context.find_var(args.back());
		if (arg[counter] == DBL_MIN)
		{
			if (!check(args.back()))
				throw invalid_arg();
			arg[counter] = std::stod(args.back());
		}
		args.pop_back();
		counter++;
	}
	while (counter != 2)
	{
		arg[counter] = context.pop_arg();
		counter++;
	}
	if (!arg[0])
		throw division_by_zero();
	context.push_arg(arg[1] / arg[0]); 
}

void Sqrt::make_operation(Context& context, list<string>& args)
{
	double arg;
	if (args.size() + context.size_arg() < 1)
		throw empty_args();
	int counter = 0;
	if (args.size())
	{
		arg = context.find_var(args.back());
		if (arg == DBL_MIN)
		{
			if (!check(args.back()))
				throw invalid_arg();
			arg = std::stod(args.back());
		}
		args.pop_back();
	} 
	else 
		arg = context.pop_arg();
	if (arg < 0)
		throw negative_number();
	context.push_arg(sqrt(arg));
}

void Pop::make_operation(Context& context, list<string>& args)
{
	if (context.size_arg() <= 0)
		throw empty_stack();
	context.pop_arg();
}

void Push::make_operation(Context& context, list<string>& args)
{
	
	double arg = DBL_MIN;
	if (!context.is_empty_var())
		arg = context.find_var(args.back());
	if (arg == DBL_MIN)
	{
		if (!check(args.back()))
			throw invalid_arg();
		arg = std::stod(args.back());
	}	
	args.pop_back();
	context.push_arg(arg);
}

void Print::make_operation(Context& context, list<string>& args)
{
	if (!context.size_arg())
		throw empty_stack();
	std::cout << context.top_arg();
}

void Define::make_operation(Context& context, list<string>& args)
{
	if (!args.size())
		throw empty_args();
	std::string variable = args.back();
	args.pop_back();
	std::string name = args.back();
	if (!check(args.back()))
		throw invalid_arg();
	context.add_var(name, std::stod(variable));
}
