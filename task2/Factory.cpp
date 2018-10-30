#include "Factory.h"
#include "Exceptions.h"

Factory* Factory::get_instance()
{
	static Factory factory;
	return &factory;
}

void Factory::make_command(const std::string key, OperatorCreater* value)
{
	switcher[key] = value;
}

Operator* Factory::get_operator(std::string name)
{
	if (switcher.find(name) == switcher.end())
		throw no_operation();
	return switcher.at(name)->create(); 
}

Factory::~Factory()
{
	for (auto i = switcher.begin(); i != switcher.end(); i++)
		delete i->second;
}
