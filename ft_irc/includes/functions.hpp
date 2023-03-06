/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:43:00 by charleshajj       #+#    #+#             */
/*   Updated: 2023/03/07 00:18:04 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

std::string              itoa(int a);
std::vector<std::string> split(const std::string &str, const std::string &delimiters);
std::string              to_lower(std::string str);

#endif