/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Away.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charleshajjar <charleshajjar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:49:42 by charleshajj       #+#    #+#             */
/*   Updated: 2023/02/27 15:07:08 by charleshajj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWAY_H
#define AWAY_H

// Our includes
#include "../Command.hpp"

class Away : public Command
{
  public:
	Away()
	{
		_name = "away";
		_description = "request  a private msg";
		_usage = "away";
		_example[0] = "away :[msg]";
	}

	void execute()
	{
	}
};
#endif