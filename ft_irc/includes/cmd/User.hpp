#ifndef USER_H
#define USER_H


#include "../Command.hpp"

#define _name
#define _decription 
class User : public Command
{
  public:
	User()
	{
		_description = "end a session";
		_usage = "user";
		_example[0] = "user <number of user> <number of  host> < number of  "
		              "server>: <number>";
		_example[1] = "user telnet";
		_needs_auth = false;
	}

	void execute()
	{
		if (_message->getParams().size() == 0 || _message->getParams().size() > 4)
		{
			_sender->message("Please send valid params! Ex: user <username> "
			                 "<hostname> <servername> : <realname>\n");
		}
		else
		{
			std::string username = _message->getParams()[0];
			std::string realname = _message->getParams()[3];

			if (_sender->_username == username)
			{
				_sender->message("You can't assign the same name yourself!\n");
			}
			else
			{
				for (size_t i = 0; i < _server->_clients.size(); i++)
				{
					if (_server->_clients[i]->_username == username)
					{
						_sender->message(ERR_NICKNAMEINUSE(_sender->_servername, username));
						return;
					}
				}
				_sender->setUsername(username);
				_sender->setRealName(realname);
				if (!_sender->isAuthenticated() && !_server->hasPassword())
					_sender->authenticate();
			}
		}
	}
};
#endif
