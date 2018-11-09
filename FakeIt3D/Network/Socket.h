#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Config.h"

class Socket
{
public:
	using SocketHandle = SOCKET;
	/*
		Status codes that may be returned by socket functions
	*/
	enum Status
	{
		Done, 
		NotReady,
		Partial,
		Disconnected,
		Error
	};

public:
	/*
		Set the blocking state of the socket

	*/
	void setBlocking(bool _blocking);

protected:
	enum Type
	{
		TCP,	// TCP protcol
		UDP		// UDP protcol
	};

	Socket(Type _type);

	void create(LPADDRINFO _addr);

	void create(SocketHandle handle);

	void close();

	Socket::Status createAddress(const char* _address, const char* _port, LPADDRINFO& _addr);

	SocketHandle getHandle() const;

	Socket::Status getErrorStatus() const; 

private:
	Type			m_type;
	SocketHandle	m_socket;
	bool			m_isBlocking;
};
