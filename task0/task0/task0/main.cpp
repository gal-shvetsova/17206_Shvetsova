#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Hello world!" << "\n";

	std::cout << Module1::getMyName() << "\n";
	std::cout << Module2::getMyName() << "\n";

	using namespace Module1;
	std::cout << getMyName() << "\n"; // (A)

	//Выведется значение функции getMyName() (John) из пространства имен Module1
	//т.к. с помощью using namespace Module1; были определены все
	//имена из пространства Module1

	std::cout << Module2::getMyName() << "\n";

	//using namespace Module2; // (B)
	//std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)

	//Ошибка происходит т.к. в обоих пространствах имен есть одно и то же имя
	//Исправить: 1. обеспечить доступ к нужному имени без использования using / using namespace:
	//				std::cout << Module2::getMyName() << "\n";
	//			 2. обеспечить доступ через директиву using
	//				using Module2::getMyName;
	//				std::cout << getMyName() << "\n";
	using Module2::getMyName;
	std::cout << getMyName() << "\n"; // (D)

	//Выведется значение функции getMyName() (James) из пространства имен Module2
	//т.к. с помощью using Module2::getMyName; было определено имя getMyName.
	//using имеет больший приоритет, чем using namespace, поэтому не возникает ошибки

	using std::cout;  //Определение имени cout из пространства имен позволяет использовать cout вместо std::cout
	cout << Module3::getMyName() << "\n";


	int a;
	std::cin >> a;  //some changes to second question in task 0a
	return 0;
}
