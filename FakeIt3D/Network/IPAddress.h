#pragma once
#include "Config.h"
#include <string>


class IPAddress
{
public:

	/*
		Default constructor

		This constructor creates an empty (invalid) address
	*/
	IPAddress();

	/*
		Construct the address from a string

		Params:
		address		IP address or network name
	*/
	IPAddress(const std::string& _address);

	IPAddress(Uint8 _a, Uint8 _b, Uint8 _c, Uint8 _d);

	Uint32 ToInteger() const;
	std::string ToStr() const;

	static const IPAddress Any;
	static const IPAddress Localhost;

private:

	void resolve(const std::string& _address);
private:
	std::string m_addressStr;
	Uint32	m_address;
	bool	m_valid;
};

