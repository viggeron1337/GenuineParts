#pragma once
#include "Socket.h"
#include "IPAddress.h"
#include "Packet.h"

class TCPListener;
class TCPSocket : public Socket
{
public:
	/*
		Default Constructor
	*/
	TCPSocket();

	Status Connect(const IPAddress& _remoteadr, const char* _remotePort);

	Status Send(const void* data, unsigned int size, unsigned int& sent);

	Status Send(Packet& packet);

	Status Receive(void* data, std::size_t size, std::size_t& received);

	Status Receive(Packet& packet);

	void Disconnect();
private:
	friend class TCPListener;

	struct PendingPacket
	{
		PendingPacket();

		Uint32 Size;
		std::size_t SizeReceived;
		Vector<char> Data;
	};

	PendingPacket m_pendingPacket;

};

