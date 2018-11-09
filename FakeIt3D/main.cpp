
#include "Utility/Vector.h"
#include <iostream>
#include <algorithm>
#include "Network/TCPListener.h"
int main()
{
	
	TCPSocket s;
	
	if (s.Connect(IPAddress::Localhost, "27015") == Socket::Status::Done)
	{
		std::cout << "Connected to server!" << std::endl;
	}

	s.Disconnect();
	
	system("pause");
	return 0;
}