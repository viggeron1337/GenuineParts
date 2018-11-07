#include "Socket.h"
#include <iostream>

struct SocketInit
{
	SocketInit()
	{
		WSADATA init;
		WSAStartup(MAKEWORD(2, 2), &init);
	}

	~SocketInit()
	{
		WSACleanup();
	}
};

////////////////////////////////////////////////////
Socket::Socket(Type _type):
m_type			(_type),
m_socket		(INVALID_SOCKET),
m_isBlocking	(false)
{
}

////////////////////////////////////////////////////
void Socket::create()
{
	if (m_socket == INVALID_SOCKET)
	{
		SocketHandle handle = socket(PF_INET, m_type == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);

		if (handle == INVALID_SOCKET)
		{
			std::cerr << __FILE__ << std::endl;
		}


	}
}

////////////////////////////////////////////////////
void Socket::create(SocketHandle handle)
{
	if (m_socket == INVALID_SOCKET)
	{
		m_socket = handle;

		setBlocking(m_isBlocking);
		
		if (m_type == TCP)
		{
			// Disable the Nagle algorithm https://en.wikipedia.org/wiki/Nagle%27s_algorithm
			int yes = 1;
			if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
			{
				std::cerr << __FILE__ << std::endl;
			}
		}
		else // UDP
		{
			// Enable broadcast by default for UDP sockets
			int yes = 1;
			if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
			{
				std::cerr << __FILE__ << std::endl;
			}
		}
		
	}
}

////////////////////////////////////////////////////
void Socket::close()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

sockaddr_in Socket::createAddress(Uint32 _address, Uint16 _port)
{
	sockaddr_in addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_addr.s_addr = htonl(_address);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);

	return addr;
}


////////////////////////////////////////////////////
void Socket::setBlocking(bool _blocking)
{
	u_long blocking = _blocking ? 0 : 1;
	ioctlsocket(m_socket, FIONBIO, &blocking);
	
	m_isBlocking = _blocking;
}

