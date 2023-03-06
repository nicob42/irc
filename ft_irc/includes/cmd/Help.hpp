/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Help.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charleshajjar <charleshajjar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:25:29 by charleshajj       #+#    #+#             */
/*   Updated: 2023/02/28 15:30:05 by charleshajj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELP_H
#define HELP_H

#include "../Command.hpp"

class Help : public Command
{
  public:
	Help()
	{
		_name = "?\help";
		_description = "infos help";
		_usage = "?\help";
		_example[0] = "?\help";
	}

	void execute()
	{
	}
};
#endif