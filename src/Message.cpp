/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:31:43 by ncheniou          #+#    #+#             */
/*   Updated: 2026/11/11 09:36:49 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Utils.hpp"

Message::Message(const std::string &line)
{
	size_t	i = 0;
	size_t	len = line.size();

	if (i < len && line[i] == ':')
	{
		while (i < len && line[i] != ' ')
			++i;
	}
	while (i < len && line[i] == ' ')
		++i;

	size_t start = i;
	while (i < len && line[i] != ' ')
		++i;
	command = toUpper(line.substr(start, i - start));

	while (i < len)
	{
		while (i < len && line[i] == ' ')
			++i;
		if (i >= len)
			break;
		if (line[i] == ':')
		{
			params.push_back(line.substr(i + 1));
			break;
		}
		start = i;
		while (i < len && line[i] != ' ')
			++i;
		params.push_back(line.substr(start, i - start));
	}
}
