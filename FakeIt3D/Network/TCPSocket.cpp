#include "TCPSocket.h"

////////////////////////////////////////////////////
TCPSocket::TCPSocket() :
	Socket(TCP)
{

}

////////////////////////////////////////////////////
Socket::Status TCPSocket::Connect(const IPAddress & _remoteadr, const char* _remotePort)
{
	// Disconnect the socket if it is already connected
	Disconnect();

	LPADDRINFO addr_srv = nullptr;
	Status status = Socket::createAddress(_remoteadr.ToStr().c_str(), _remotePort, addr_srv);
	if (status != Status::Done)
	{
		return Socket::getErrorStatus();
	}

	Socket::create(addr_srv);


	if(connect(getHandle(), addr_srv->ai_addr, addr_srv->ai_addrlen) == -1)
	{
		return Socket::getErrorStatus();
	}

	return Done;
}

////////////////////////////////////////////////////
void TCPSocket::Disconnect()
{
	Socket::close();
}
