/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charleshajjar <charleshajjar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:25:46 by charleshajj       #+#    #+#             */
/*   Updated: 2023/02/28 15:30:59 by charleshajj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_H
#define INVITE_H

// Our includes
#include "../Command.hpp"

class Invite : public Command
{
  public:
	Invite()
	{
		_name = "invite";
		_description = "invite user in a  canal";
		_usage = "invite";
		_example[0] = "invite <nick> <canal>";
	}

	void execute()
	{
	}
};
#endif