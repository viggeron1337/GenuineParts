#include "TCPSocket.h"
#include <algorithm>
#include <iostream>

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
Socket::Status TCPSocket::Send(const void * data, unsigned int size, unsigned int & sent)
{
	if (!data || (size == 0))
	{
		std::cout << __LINE__ << std::endl;
		return Status::Error;
	}

	int result = 0;
	for (sent = 0; sent < size; sent += result)
	{
		result = send(Socket::getHandle(), static_cast<const char*>(data) + sent, static_cast<int>(size - sent), 0);

		if (result < 0)
		{
			Status status = Socket::getErrorStatus();

			if ((status == NotReady) && sent)
			{
				return Partial;
			}
			return status;
		}
	}
	return Done;
}

////////////////////////////////////////////////////
Socket::Status TCPSocket::Send(Packet & packet)
{
	unsigned int size = 0;
	
	const void* data = packet.onSend(size);

	Uint32 packetSize = htonl(static_cast<Uint32>(size));

	Vector<char> blockToSend(sizeof(packetSize) + size);

	std::memcpy(&blockToSend[0], &packetSize, sizeof(packetSize));
	if (size > 0)
		std::memcpy(&blockToSend[0] + sizeof(packetSize), data, size);

	unsigned int sent;

	Status status = Send(&blockToSend[0] + packet.m_sendPos, blockToSend.Size() - packet.m_sendPos, sent);

	if (status == Partial)
	{
		packet.m_sendPos += sent;
	}
	else if (status == Done)
	{
		packet.m_sendPos = 0;
	}

	return status;
}

////////////////////////////////////////////////////
Socket::Status TCPSocket::Receive(void * data, std::size_t size, std::size_t & received)
{
	received = 0;

	if (!data)
	{
		std::cerr << __LINE__ << std::endl;
		return Socket::Error;
	}

	int sizeReceived = recv(getHandle(), static_cast<char*>(data), static_cast<int>(size), 0);

	if (sizeReceived > 0)
	{
		received = static_cast<std::size_t>(sizeReceived);
		return Socket::Done;
	}
	else if (sizeReceived == 0)
	{
		return Socket::Disconnected;
	}
	else
	{
		return Socket::getErrorStatus();
	}
}

////////////////////////////////////////////////////
Socket::Status TCPSocket::Receive(Packet & packet)
{
	packet.Clear();

	Uint32 packetSize = 0;
	std::size_t received = 0;
	if (m_pendingPacket.SizeReceived < sizeof(m_pendingPacket.Size))
	{
		while (m_pendingPacket.SizeReceived < sizeof(m_pendingPacket.Size))
		{
			char* data = reinterpret_cast<char*>(&m_pendingPacket.Size) + m_pendingPacket.SizeReceived;
			Status status = Receive(data, sizeof(m_pendingPacket.Size) - m_pendingPacket.SizeReceived, received);
			m_pendingPacket.SizeReceived += received;

			if (status != Socket::Done)
			{
				return status;
			}

		}

		packetSize = ntohl(m_pendingPacket.Size);
	}
	else
	{
		packetSize = ntohl(m_pendingPacket.Size);
	}

	char buffer[1024];
	while (m_pendingPacket.Data.Size() < packetSize)
	{
		std::size_t sizeToGet = (std::min)(static_cast<std::size_t>(packetSize - m_pendingPacket.Data.Size()), sizeof(buffer));
		Status status = Receive(buffer, sizeToGet, received);
		if (status != Done)
			return status;

		if (received > 0)
		{
			m_pendingPacket.Data.Resize(m_pendingPacket.Data.Size() + received);
			char* begin = &m_pendingPacket.Data[0] + m_pendingPacket.Data.Size() - received;
			std::memcpy(begin, buffer, received);
		}
	}

	if (!m_pendingPacket.Data.empty())
	{
		packet.onReceive(&m_pendingPacket.Data[0], m_pendingPacket.Data.Size());
	}

	m_pendingPacket = PendingPacket();

	return Socket::Done;
}

////////////////////////////////////////////////////
void TCPSocket::Disconnect()
{
	Socket::close();
}

////////////////////////////////////////////////////
TCPSocket::PendingPacket::PendingPacket() :
Size		(0),
SizeReceived(0),
Data		()
{
}
