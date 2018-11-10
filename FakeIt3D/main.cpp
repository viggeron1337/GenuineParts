#include "Utility/Vector.h"
#include <iostream>
#include "Network/TCPSocket.h"

class Person
{
private:
	int age;
	int age2;
	double lol;
public:
	Person(int a, int a2, double l)
	{
		age = a;
		age2 = a2;
		lol = l;
	}
};

int main()
{
	TCPSocket s;

	Packet p;

	Person p2(20, 30, 6.7);
	p << p2;

	Person p3(0, 0, 0);
	
	p >> p3;

	

	system("pause");
	return 0;
}