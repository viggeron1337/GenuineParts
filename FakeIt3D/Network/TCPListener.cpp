#include "TCPListener.h"

////////////////////////////////////////////////////
TCPListener::TCPListener() : Socket(TCP)
{

}

Socket::Status TCPListener::Listen(const char* _port)
{
	Socket::close();

	LPADDRINFO addr_srv = nullptr;
	if (Socket::createAddress(IPAddress::Any.ToStr().c_str(), _port, addr_srv) != Done)
	{
		return Socket::getErrorStatus();
	}

	Socket::create(addr_srv);

	if (bind(Socket::getHandle(), addr_srv->ai_addr, static_cast<int>(addr_srv->ai_addrlen)) == -1)
	{
		return Socket::getErrorStatus();
	}

	if (listen(Socket::getHandle(), SOMAXCONN) == -1)
	{
		return Socket::Error;
	}
	return Socket::Done;
}

Socket::Status TCPListener::Accept(TCPSocket & _socket)
{
	if (Socket::getHandle() == INVALID_SOCKET)
	{
		return Error;
	}

	sockaddr_in address;
	int addrLength = sizeof(address);
	SocketHandle remote = accept(Socket::getHandle(), reinterpret_cast<sockaddr*>(&address), &addrLength);

	if (remote == INVALID_SOCKET)
	{
		return Socket::getErrorStatus();
	}

	_socket.close();
	_socket.create(remote);

	return Done;
}
