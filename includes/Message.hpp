/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:31:03 by ncheniou          #+#    #+#             */
/*   Updated: 2026/11/11 09:33:02 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>

struct Message
{
	std::string					command;
	std::vector<std::string>	params;

	explicit Message(const std::string &line);
};

#endif
