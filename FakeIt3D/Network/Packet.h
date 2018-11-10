#pragma once
#include "../Utility/Vector.h"
#include "Config.h"

class TCPSocket;
class Packet
{
public:
	Packet();

	void Append(const void* data, std::size_t sizeInBytes);
	const void* getData() const;
	unsigned int GetDataSize() const;

	void Clear();

	const void* onSend(unsigned int& _size);
	void onReceive(const void* data, std::size_t size);

	template<class T>
	Packet& operator>>(T& data);
	template<class T>
	Packet& operator<<(T& data);

	Packet& operator>>(Int8& data);
	Packet& operator<<(Int8& data);

	Packet& operator>>(Uint8& data);
	Packet& operator<<(Uint8& data);


private:
	bool CheckSize(std::size_t size);
private:
	friend class TCPSocket;

	Vector<char>	m_data;
	int				m_sendPos;
	int				m_readPos;
	bool			m_isValid;

};

template<class T>
Packet & Packet::operator>>(T & data)
{
	if (CheckSize(sizeof(data)))
	{
		data = *(reinterpret_cast<const T*>(&m_data[m_readPos]));
		m_readPos += sizeof(data);
	}
	return *this;
}

template<class T>
Packet & Packet::operator<<(T & data)
{
	Append(&data, sizeof(data));
	return *this;
}
