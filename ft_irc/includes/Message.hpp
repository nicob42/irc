/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:42:16 by charleshajj       #+#    #+#             */
/*   Updated: 2023/03/07 00:18:06 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
#define MESSAGE_H

// Our includes
#include "./Color.hpp"
#include "./functions.hpp"

#include <cstring>
#include <iostream>
#include <map>
#include <string>

class Message
{
  public:
	std::string _buffer;

  private:
	std::string                   _cmd;
	std::map<size_t, std::string> _params;

  public:
	Message(std::string &buffer);
	std::string                   getCmd(void) const;
	std::map<size_t, std::string> getParams(void) const;
};

#endif