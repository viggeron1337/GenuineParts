#include "Utility/Vector.h"
#include <vector>
#include<iostream>

class Test
{
public:
	int x;
	Test() : x(0)
	{
		std::cout << "Copy Conctructor(myvec)" << std::endl;
	}

	~Test()
	{
		std::cout << "Destructor(myvec)" << std::endl;
	}
};

class Test2
{
public:
	int x;
	Test2() : x(0)
	{
		std::cout << "Copy Conctructor(realvec)" << std::endl;
	}

	~Test2()
	{
		std::cout << "Destructor(realvec)" << std::endl;
	}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Vector<Test> test;
	std::vector<Test2> realVec;

	test.Reserve(30);
	realVec.reserve(30);

	assert(test.Size() == 0);
	assert(realVec.size() == 0);

	test.Resize(20);
	realVec.resize(20);

	assert(test.Size() == 20);
	assert(realVec.size() == 20);

	for (int i = 0; i < 20; i++)
	{
		test[i].x = realVec[i].x = i;
		assert(test[i].x == realVec[i].x);
	}

	test.clear();
	realVec.clear();

	assert(test.Size() == 0);
	assert(realVec.size() == 0);


	for (int i = 0; i < 20; i++)
	{
		Test t;
		Test2 t2;
		t.x = i;
		t2.x = i;
		test.PushBack(t);
		realVec.push_back(t2);
		test[i].x = realVec[i].x = i;
		assert(test[i].x == realVec[i].x);
	}

	for (int i = 0; i < 20; i++)
	{
		assert(test.Front().x == realVec.front().x);
		test.PopBack();
		realVec.pop_back();

	}




	return 0;
}
