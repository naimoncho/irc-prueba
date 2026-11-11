/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:31:11 by ncheniou          #+#    #+#             */
/*   Updated: 2026/11/11 09:33:57 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <vector>


std::string					toLower(const std::string &s);
std::string					toUpper(const std::string &s);

std::vector<std::string>	split(const std::string &s, char sep);

std::string					toString(long n);

bool						isValidNick(const std::string &nick);
bool						isValidChannelName(const std::string &name);

#endif
