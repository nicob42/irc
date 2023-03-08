#ifndef STATUS_H
#define STATUS_H


#include "../Command.hpp"

class Status : public Command
{
  public:
	Status()
	{
		_name = "status";
		_description = "Displays the current state of Telnet";
		_usage = "status";
		_example[0] = "status";
	}

	void execute()
	{
	}
};
#endif
