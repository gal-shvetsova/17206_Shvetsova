#include "Calculator.h"
#include <string>
#include <iostream>
#include "Context.h"
#include "Creator.h"
#include "Exceptions.h"
#include "Factory.h"
#include "Operator.h"

void Calculator::compute(std::istream& in, std::ostream& out)
{
	Context context;
	string buffer, operation;
	OperatorCreater creator;
	while (!in.eof())
	{
		std::getline(in, buffer, '\n');
		context.get_arg_l(buffer);
		try
		{
			if (!context.size_l())
			{
				throw empty_args();
			}
		}
		catch (calc_except& exc)
		{
			out << exc.what() << "\n";
			continue;
		}
		operation = context.front_l();
		context.pop_front_l();
		if (operation.front() != '#')
		{
			try
			{
				Operator*  some_oper = Factory::get_instance()->get_operator(operation);

				some_oper->make_operation(context);
			}
			catch (calc_except& exc)
			{
				out << exc.what() << "\n";
			}
		}

	}
}