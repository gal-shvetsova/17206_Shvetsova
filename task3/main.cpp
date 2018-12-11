#include <iostream>
#include "Model.h"
#include "View.h"
#include "Basic_Gamers.h"
#include "SeaBattle.h"
#include <time.h>
#include "optionparser.h"
#include <string>

static option::ArgStatus gamerType(const option::Option &option, bool error) 
{
	if (option.arg != nullptr && (strcmp(option.arg, "random") == 0 || strcmp(option.arg, "console") == 0 ||
		strcmp(option.arg, "optimal") == 0))
		return option::ARG_OK;

	if (error)
		std::cout << "Error";
	return option::ARG_ILLEGAL;
}

static option::ArgStatus countType(const option::Option &option, bool error) 
{
	char *endptr = nullptr;
	if (option.arg != nullptr && strtol(option.arg, &endptr, 10)) {};
	if (endptr != option.arg && *endptr == 0)
		return option::ARG_OK;

	if (error)
		std::cout << "Error";
	return option::ARG_ILLEGAL;
}

enum optionIndex 
{
	ROUNDS, PLAYER, HELP
};
enum optionType 
{
	FIRST, SECOND
};

const option::Descriptor usage[] = 
{
		{ROUNDS, 0,      "c", "count",  countType,           "-c, --count \t| Rounds \t|Default: 1"},
		{PLAYER, FIRST,  "f", "first",  gamerType,        "-f, --first \t| First gamer \t|Default: random"},
		{PLAYER, SECOND, "s", "second", gamerType,        "-s, --second \t| Second gamer \t|Default: random"},
		{HELP,   0,      "h", "help",   option::Arg::None, "-h, --help \t| Help"}
};

int main(int argc, char *argv[]) 
{	
	argc -= (argc > 0); argv += (argc > 0); // skip program name argv[0] if present
	option::Stats stats(usage, argc, argv);
	option::Option* options = new option::Option[stats.options_max];
	option::Option* buffer = new option::Option[stats.buffer_max];
	option::Parser parser(usage, argc, argv, options, buffer);

	if (parser.error())
		return 1;
	if (options[HELP]){
		option::printUsage(std::cout, usage);
		return 0;
	}

	int rounds = 1;
	std::string firstType = "", secondType = "";
	if (options[ROUNDS])
		rounds = atoi(options[ROUNDS].last()->arg); 
	for (option::Option *opt = options[PLAYER]; opt; opt = opt->next()) {
		switch (opt->type()) {
		case FIRST:
			firstType = opt->arg;
			break;
		case SECOND:
			secondType = opt->arg;
			break;
		default:
			return 2;
		}
	}
	if (!firstType.size())
		firstType = "random";
	if (!secondType.size())
		secondType = "random";

	srand(time(NULL));
	SeaBattle seabttl;
	seabttl.Play(firstType, secondType, rounds);
	return 0;
}