#include "TCPSocket.h"

////////////////////////////////////////////////////
TCPSocket::TCPSocket() :
Socket(TCP)
{

}

Socket::Status TCPSocket::Connect(const IPAddress & _remoteadr, Uint16 _remotePort)
{
	// Disconnect the socket if it is already connected
	Disconnect();

	create();

	sockaddr_in address = createAddress(_remoteadr.ToInteger(), _remotePort);


	return Status();
}

void TCPSocket::Disconnect()
{
	Socket::close();
}
