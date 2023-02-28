/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charleshajjar <charleshajjar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:26:08 by charleshajj       #+#    #+#             */
/*   Updated: 2023/02/28 15:37:59 by charleshajj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_H
#define JOIN_H

#include "../Command.hpp"

class Join : public Command
{
  public:
	Join()
	{
		_name = "join";
		_description = "see all canale or générate new canal "
		               "canal";
		_usage = "join <canal>{,<canal>} [<clave>{,<clave>}]";
		_example[0] = "join #canal1 clave1";
		_example[1] = "join #canal1,#canal2 clave1,clave2";

	}
	
};
#endif
