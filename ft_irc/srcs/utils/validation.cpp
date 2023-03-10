#include "../../includes/Server.hpp"

bool validate_args(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		std::cerr << "Usage: ./ircserv [port] [password]" << std::endl;
		return false;
	}
	int port = std::atoll(argv[1]);
	if (port <= 0)
	{
		std::cerr << "Port must be a number" << std::endl;
		return false;
	}
	else if (port > 65535)
	{
		std::cerr << "Port must be between 0 and 65535" << std::endl;
		return false;
	}
	return true;
}