#include "GameWindow.h"
#include "ForwardRenderer.h"
#include "Utility/Vector.h"
#include <iostream>
#include <algorithm>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Vector<test> lol;
	test t;
	t.x = 20;
	t.y = 20;
	lol.PushBack(t);
	t.x = 30;
	t.y = 30;
	lol.PushBack(t);

	t.x = 40;
	t.y = 40;
	lol.PushBack(t);
	
	for (auto& test : lol)
	{
		std::cout << test.x << " " << test.y << std::endl;
	}

	
	
	
	system("pause");
	return 0;
}