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

	//��������� �������� ������� getMyName() (John) �� ������������ ���� Module1
	//�.�. � ������� using namespace Module1; ���� ���������� ���
	//����� �� ������������ Module1

	std::cout << Module2::getMyName() << "\n";

	//using namespace Module2; // (B)
	//std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)

	//������ ���������� �.�. � ����� ������������� ���� ���� ���� � �� �� ���
	//���������: 1. ���������� ������ � ������� ����� ��� ������������� using / using namespace:
	//				std::cout << Module2::getMyName() << "\n";
	//			 2. ���������� ������ ����� ��������� using
	//				using Module2::getMyName;
	//				std::cout << getMyName() << "\n";
	using Module2::getMyName;
	std::cout << getMyName() << "\n"; // (D)

	//��������� �������� ������� getMyName() (James) �� ������������ ���� Module2
	//�.�. � ������� using Module2::getMyName; ���� ���������� ��� getMyName.
	//using ����� ������� ���������, ��� using namespace, ������� �� ��������� ������

	using std::cout;  //����������� ����� cout �� ������������ ���� ��������� ������������ cout ������ std::cout
	cout << Module3::getMyName() << "\n";


	int a;
	std::cin >> a;  //some changes to second question in task 0a
	return 0;
}
