#ifndef LIST_H
#define LIST_H

// Our includes
#include "../Command.hpp"

class List : public Command
{
  public:
	List()
	{
		_name = "list";
		_description = "gives a listing of all the channels on a server";
		_usage = "list [<canales>]";
		_example[0] = "list vs him";
		_example[1] = "list";
		_example[2] = "list vs them";
	}

	bool validate(void)
	{
		// TODO: Check if channel exists.
		std::map<size_t, std::string> p = _message->getParams();
		if (p.size() > 1)
		{
			_sender->message("Wrong command format. Ex: list "
			                 "[<canal>{,<canal>}]\n");
			return (false);
		}
		std::vector<std::string> _ch_params = split(p[0], ",");

		for (size_t i = 0; i < _ch_params.size(); i++)
		{
			if (_ch_params[i][0] != '#') 
			{
				_sender->message(ERR_BADCHANMASK(_sender->_servername, _sender->_nick)); // ERR_BADCHANMASK (476)
				return (false);
			}
		}
		return (true);
	}

	void execute()
	{
		std::map<size_t, std::string> p = _message->getParams();
		_sender->message(RPL_LISTSTART(_sender->_servername, _sender->_nick)); // RPL_LISTSTART (321)
		if (p.size() == 1)
		{
			std::vector<std::string> _ch_params = split(p[0], ",");

			for (size_t i = 0; i < _ch_params.size(); i++)
			{
				Channel *channel = _server->getChannel(_ch_params[i]);
				_sender->message(RPL_LIST(_sender->_servername, _sender->_nick,
				                          channel->getName(),
				                          itoa(channel->getClients().size()),
				                          channel->getTopic())); // RPL_LIST (322)
			}
		}
		else
		{
			std::vector<Channel *> channels = _server->getChannels();
			for (size_t i = 0; i < channels.size(); i++)
			{
				_sender->message(RPL_LIST(_sender->_servername, _sender->_nick,
				                          channels[i]->getName(),
				                          itoa(channels[i]->getClients().size()),
				                          channels[i]->getTopic())); // RPL_LIST (322)
			}
		}
		_sender->message(RPL_LISTEND(_sender->_servername, _sender->_nick)); // RPL_LISTEND (323)
	}
};
#endif
