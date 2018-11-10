#pragma once
#include "../Utility/Vector.h"
#include "Config.h"
#include <string>

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

	template<>
	Packet & operator>>(std::string & data);

	template<>
	Packet& operator <<(std::string& data);

private:
	bool CheckSize(std::size_t size);
private:
	friend class TCPSocket;

	Vector<char>	m_data;
	int				m_sendPos;
	int				m_readPos;
	bool			m_isValid;

};

////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
template<>
Packet & Packet::operator>>(std::string & data)
{
	Uint32 length = 0;
	*this >> length;
	data.clear();

	if ((length > 0) && CheckSize(sizeof(length)))
	{
		data.assign(&m_data[m_readPos], length);

		m_readPos += length;
	}
	return *this;
}
#include <iostream>
////////////////////////////////////////////////////////////
template<>
Packet& Packet::operator <<(std::string& data)
{
	// First insert string length
	Uint32 length = static_cast<Uint32>(data.size());
	std::cout << "String size" << length << std::endl;
	*this << length;

	// Then insert characters
	if (length > 0)
		Append(data.c_str(), length * sizeof(std::string::value_type));

	return *this;
}

////////////////////////////////////////////////////////////
template<class T>
Packet & Packet::operator<<(T & data)
{
	Append(&data, sizeof(data));
	return *this;
}
