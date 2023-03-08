#ifndef WHO_H
#define WHO_H

#include "../Command.hpp"

class Who : public Command
{
  public:
	Who()
	{
		_name = "who";
		_description = "information about the user";
		_usage = "who";
		_example[0] = "who [<number> [<o>]]";
		_example[1] = "who #them";
	}

	void execute()
	{
	}
};
#endif
