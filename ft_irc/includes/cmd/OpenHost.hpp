#ifndef OPENHOST_H
#define OPENHOST_H

// Our includes
#include "../Command.hpp"

class Openhost : public Command
{
  public:
	Openhost()
	{
		_name = "open host";
		_description = "establish a connection to the specified host. Sinon"
						"specify a port, the connection will be on the port"
						"telnet default(21). Host can't have a name or "
						"ip" ;
		_usage = "open host [port]";
		_example[0] = "open host [port]";
	}

	void execute()
	{
	}
};
#endif
