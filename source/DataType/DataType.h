#pragma once
#include <string>

enum class ConnectStatus
{
	NotConnected = 0,
	Connecting = 1,
	Connected = 2,
	DisConnecting = 3,
};

enum class LogonStatus
{
	NotLogged = 0,
	Logging = 1,
	Logged = 2,
	Logout = 3,
};

struct IPAddress
{
	std::string IP;
	int Port;
};