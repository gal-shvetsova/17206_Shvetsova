#ifndef	FACTORY_H
#define FACTORY_H
#include <map>
#include "Creator.h"

class Factory
{
private:
	Factory() = default;
	std::map <std::string, OperatorCreater*> switcher;
public:
	Factory(Factory&) = delete;
	static Factory* get_instance();
	void make_command(const std::string key, OperatorCreater* value);
	Operator* get_operator(std::string name);
	~Factory();
};

#endif