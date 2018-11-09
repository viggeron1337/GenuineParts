#pragma once
#include "Socket.h"
#include "IPAddress.h"

class TCPListener;
class TCPSocket : public Socket
{
public:
	/*
		Default Constructor
	*/
	TCPSocket();

	Status Connect(const IPAddress& _remoteadr, const char* _remotePort);

	void Disconnect();
private:
	friend class TCPListener;

};

