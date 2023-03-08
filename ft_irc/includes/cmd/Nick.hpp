#ifndef NICK_H
#define NICK_H

#include "../Command.hpp"

class Nick : public Command
{
  public:
	Nick()
	{
		_name = "nick";
		_description = "";
		_usage = "nick";
		_example[0] = "nick <them>";
		_example[1] = "nick <him>";
		_needs_auth = false;
	}

	bool validate(void)
	{
		std::map<size_t, std::string> p = _message->getParams();
		if (p.size() == 0 || p.size() > 2)
		{
			_sender->message("Wrong command format. Ex: nick <nick>\n");
			return (false);
		}
		std::string name = _message->getParams()[0];
		for (size_t i = 0; i < _server->_clients.size(); i++)
		{
			if (_server->_clients[i]->_nick == name)
			{
				_sender->message(ERR_NICKNAMEINUSE(_sender->_servername, name));
				return (false);
			}
		}
		return (true);
	}

	void execute()
	{
		std::vector<Client *> clients = _server->_clients;
		std::string           name = _message->getParams()[0];

		for (size_t i = 0; i < clients.size(); i++)
		{
			clients[i]->message(std::string(":" + _sender->_nick + "!" + _sender->_username + "@" +
			                                _sender->_servername + " NICK :" + name + "\n")
			                        .c_str());
		}
		_sender->setNick(name);
	}
};
#endif
