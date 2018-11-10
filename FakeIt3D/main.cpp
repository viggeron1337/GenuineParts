#include <iostream>
#include "Network/TCPSocket.h"
#include "Network/TCPListener.h"

const char* G_PORT = "27015";

void Server()
{
	TCPListener listener;
	Socket::Status status;

	status = listener.Listen(G_PORT);
	if(status == Socket::Done)
		std::cout << "Bound on (" << G_PORT << ")\n";
	else 
		return;

	TCPSocket s;
	status = listener.Accept(s);
	if (status == Socket::Done)
		std::cout << "Accepted a socket!" << std::endl;
	else
		return;
	do
	{
		Packet p;
		status = s.Receive(p);
		
		std::string str;
		p >> str;
		std::cout << str << std::endl;

	} while (status == Socket::Done);
}

void Client()
{
	TCPSocket s;

	if (s.Connect(IPAddress::Localhost, G_PORT) == Socket::Status::Done)
	{
		
		std::string str;
		do
		{
			Packet p;

			
			std::getline(std::cin, str);
			p << str;
			s.Send(p);
		} while (str[0] != 'q');
	}
	
}
int main()
{
	int val; 
	std::cin >> val;
	std::cin.ignore();
	if (val == 1)
	{
		Server();
	}
	else
	{
		Client();
	}
	
	return 0;

	system("pause");
}