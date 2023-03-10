/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Close.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charleshajjar <charleshajjar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:04:08 by charleshajj       #+#    #+#             */
/*   Updated: 2023/02/27 15:07:06 by charleshajj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
#define CLOSE_H

// Our includes
#include "../Command.hpp"

class Close : public Command
{
  public:
	Close()
	{
		_name = "close";
		_description = "terminate session";
		_usage = "close";
		_example[0] = "close";
	}

	void execute()
	{
	}
};
#endif