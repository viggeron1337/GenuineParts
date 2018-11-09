#pragma once
#include "IPAddress.h"
#include "TCPSocket.h"

class TCPListener : public Socket
{
public:

	TCPListener();

	Socket::Status Listen(const char* _port);

	Socket::Status Accept(TCPSocket& _socket);
};
