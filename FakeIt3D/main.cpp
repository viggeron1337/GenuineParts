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
	
	Vector<TCPSocket> sockets;
	
	listener.setBlocking(false);
	while(true)
	{
		TCPSocket newSock;
	
		status = listener.Accept(newSock);
		if (status == Socket::Done)
		{
			std::cout << "new socket accepted!" << std::endl;
			newSock.setBlocking(false);
			sockets.PushBack(newSock);
		}

		for (int i = 0; i < sockets.Size(); i++)
		{
			Packet p;
			status = sockets[i].Receive(p);
			if (status == Socket::Done)
			{
				for (int j = 0; j < sockets.Size(); j++)
				{
					if (j != i)
					{
						sockets[j].Send(p);
					}
				}
			}

		}

	}
}

void Client()
{
	TCPSocket s;
	
	if (s.Connect(IPAddress::Localhost, G_PORT) == Socket::Status::Done)
	{
		s.setBlocking(false);
		std::string str;
		do
		{
			Packet p;
			s.Receive(p);
			if (p.GetDataSize())
			{
				p >> str;
				std::cout << str << std::endl;
			}
			
			std::getline(std::cin, str);
			if (str.size())
			{
				p << str;
				s.Send(p);
			}
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