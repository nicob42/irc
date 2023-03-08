#ifndef WHOIS_H
#define WHOIS_H

#include "../Command.hpp"

class Whois : public Command
{
  public:
	Whois()
	{
		_name = "whois";
		_description = "info about the user using the mask";
		_usage = "whois";
		_example[0] = "whois <mask>[,<mask>[,...]]";
		_example[1] = "whois them";
	}

	void execute()
	{
	}
};
#endif
