#ifndef NOTICE_H
#define NOTICE_H

#include "../Command.hpp"

class Notice : public Command
{
  public:
	Notice()
	{
		_name = "notice";
		_description = "initiates a connection to the specified host. If I dont know "
						"specify a port the connection will be on the port "
						"telnet default(21). The host can be a name or "
						"ip";
		_usage = "notice";
		_example[0] = "notice <nick> :<texto>";
		_example[1] = "notice them vs him";
	}

	bool validate(void)
	{
		std::map<size_t, std::string> p = _message->getParams();
		if (p.size() < 3)
		{
			_sender->message("Wrong command format. Ex: notice <nick> "
			                 ":<texto>\n");
			return (false);
		}
		return (true);
	}

	void execute()
	{
	}
};
#endif
