#pragma once
#include "Socket.h"
#include "IPAddress.h"

class TCPSocket : Socket
{
public:
	/*
		Default Constructor
	*/
	TCPSocket();

	Status Connect(const IPAddress& _remoteadr, Uint16 _remotePort);

	void Disconnect();
private:

};

