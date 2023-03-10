#ifndef PRIVMSG_H
#define PRIVMSG_H

// Our includes
#include "../Command.hpp"

class PrivMsg : public Command
{
  public:
	PrivMsg()
	{
		_name = "privmsg";
		_description = "Send message to a set of users/channels";
		_usage = "privmsg <receptor|channel>{,<receptor|channel>} :<texto>";
		_example[0] = "privmsg welcome firts priv msg";
		_example[1] = "privmsg welcome them";
		_example[2] = "privmsg welcome him";
		_example[3] = "privmsg welcome she/he";
	}

	bool validate(void)
	{
		std::map<size_t, std::string> p = _message->getParams();
		std::cout << "p.size() = " << p.size() << std::endl;
		if (p.size() == 0 || p.size() < 2)
		{
			_sender->message("Please send valid params! Ex: privmsg <nickname> "
			                 ":<message>\n");
			return (false);
		}
		else if (p[0].at(0) == '#')
		{
			std::vector<std::string> _ch_params = split(p[0], ",");
			for (size_t i = 1; i < _ch_params.size(); i++)
			{
				if (_ch_params[i][0] != '#')
				{
					_sender->message("Wrong command format. Ex: privmsg "
					                 "tired man\n");
					return (false);
				}
				else if (!_server->getChannel(_ch_params[i]))
				{
					_sender->message(std::string("Channel" + _ch_params[i] + "doesn't exist\n")
					                     .c_str());
					return (false);
				}
			}
		}
		else
		{
			std::vector<std::string> _cl_params = split(p[0], ",");
			for (size_t i = 0; i < _cl_params.size(); i++)
			{
				if (_server->getClient(_cl_params[i]) == NULL)
				{
					std::cout << _sender->_nick << _cl_params[i] << std::endl;
					_sender->message(ERR_NOSUCHNICK(_sender->_servername, _cl_params[i]));
					return (false);
				}
				else if (_sender->_nick == _cl_params[i])
				{
					_sender->message(
					    std::string("You cannot send a message yourself!\n").c_str());
					return (false);
				}
			}
		}
		return (true);
	}

	void execute()
	{
		std::map<size_t, std::string> p = _message->getParams();
		std::string                   msg = std::string(p[1] + "\n").c_str();
		if (p[0].at(0) == '#')
		{
			std::vector<std::string> _ch_params = split(p[0], ",");
			for (size_t i = 0; i < _ch_params.size(); i++)
			{
				std::string           name = _ch_params[i].substr(1).c_str();
				Channel *             channel = _server->getChannel(name);
				std::vector<Client *> clients = channel->getClients();
				for (size_t j = 0; j < clients.size(); j++)
				{
					if (clients[j] != _sender)
					{
						clients[j]->message(std::string(":" + _sender->_nick + " PRIVMSG #" +
						                                channel->getName() + " :" + msg + "\n")
						                        .c_str());
					}
				}
			}
		}
		else
		{
			std::vector<std::string> _cl_params = split(p[0], ",");
			for (size_t i = 0; i < _cl_params.size(); i++)
			{
				Client *client = _server->getClient(_cl_params[i]);
				client->message(
				    std::string(":" + _sender->_nick + " PRIVMSG " + client->getNick() + " :" + msg + "\n")
				        .c_str());
			}
		}
	}
};

#endif
