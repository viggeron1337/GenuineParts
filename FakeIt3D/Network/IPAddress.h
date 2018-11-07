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

	Uint32 ToInteger() const;

private:

	void resolve(const std::string& _address);
private:
	Uint32	m_address;
	bool	m_valid;
};

