#include "Socket.h"
#include <iostream>

struct SocketInit
{
	SocketInit()
	{
		std::cout << "Körs" << std::endl;
		WSADATA init;
		WSAStartup(MAKEWORD(2, 2), &init);
	}

	~SocketInit()
	{
		WSACleanup();
	}
};

SocketInit globalInit;

////////////////////////////////////////////////////
Socket::Socket(Type _type):
m_type			(_type),
m_socket		(INVALID_SOCKET),
m_isBlocking	(true)
{
}

////////////////////////////////////////////////////
void Socket::create(LPADDRINFO _addr)
{
	if (m_socket == INVALID_SOCKET)
	{
		SocketHandle handle = socket(_addr->ai_family, _addr->ai_socktype, _addr->ai_protocol);

		if (handle == INVALID_SOCKET)
		{
			std::cerr << __FILE__ << std::endl;
		}

		create(handle);

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

Socket::Status Socket::createAddress(const char* _address, const char* _port, LPADDRINFO& _addr)
{
	ADDRINFO hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	if (getaddrinfo(_address, _port, &hints, &_addr) != 0)
	{
		return Socket::getErrorStatus();
	}

	if (_addr == nullptr)
	{
		return Socket::getErrorStatus();
	}

	return Done;
}

////////////////////////////////////////////////////
Socket::SocketHandle Socket::getHandle() const
{
	return m_socket;
}

////////////////////////////////////////////////////
Socket::Status Socket::getErrorStatus() const
{
	switch (WSAGetLastError())
	{
		case WSAEWOULDBLOCK:	return Socket::NotReady;
		case WSAEALREADY:		return Socket::NotReady;
		case WSAECONNABORTED:	return Socket::Disconnected;
		case WSAECONNRESET:		return Socket::Disconnected;
		case WSAETIMEDOUT:		return Socket::Disconnected;
		case WSAENETRESET:		return Socket::Disconnected;
		case WSAENOTCONN:		return Socket::Disconnected;
		case WSAEISCONN:		return Socket::Done;
		default:				
			std::cout << WSAGetLastError() << std::endl;
			return Socket::Error;
	}
}


////////////////////////////////////////////////////
void Socket::setBlocking(bool _blocking)
{
	u_long blocking = _blocking ? 0 : 1;
	ioctlsocket(m_socket, FIONBIO, &blocking);
	
	m_isBlocking = _blocking;
}

