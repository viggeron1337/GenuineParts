#include "IPAddress.h"
#include "Socket.h"

////////////////////////////////////////////////////
IPAddress::IPAddress() :
m_address	(0),
m_valid		(false)
{
}

IPAddress::IPAddress(const std::string & _address) :
m_address	(0),
m_valid		(false)
{
	resolve(_address);
}

Uint32 IPAddress::ToInteger() const
{
	return ntohl(m_address);
}

void IPAddress::resolve(const std::string & _address)
{
	m_address = 0;
	m_valid = false;


	
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	addrinfo* result = nullptr;
	if (getaddrinfo(_address.c_str(), nullptr, &hints, &result) == 0)
	{
		if (result)
		{
			Uint32 ip = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr.s_addr;
			freeaddrinfo(result);
			m_address = ip;
			m_valid = true;
		}
	}
	

}
