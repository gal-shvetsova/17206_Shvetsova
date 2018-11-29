#include <iostream>
#include "Model.h"
#include "View.h"
#include "Basic_Gamers.h"
#include "SeaBattle.h"
#include <time.h>



int main()
{
	srand(time(NULL));
	SeaBattle seabttl;
	seabttl.Play();
	int t;
	std::cin >> t;
	return 0;
}