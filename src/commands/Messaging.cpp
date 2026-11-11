/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messaging.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:31:19 by ncheniou          #+#    #+#             */
/*   Updated: 2026/11/11 09:35:05 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Utils.hpp"

void Server::cmdPrivmsg(Client &client, const Message &msg)
{
	relay(client, msg, false);
}

void Server::cmdNotice(Client &client, const Message &msg)
{
	relay(client, msg, true);
}

void Server::relay(Client &client, const Message &msg, bool notice)
{
	const std::string command = notice ? "NOTICE" : "PRIVMSG";

	if (msg.params.empty() || msg.params[0].empty())
	{
		if (!notice)
			reply(client, "411", ":No recipient given (" + command + ")");
		return;
	}
	if (msg.params.size() < 2 || msg.params[1].empty())
	{
		if (!notice)
			reply(client, "412", ":No text to send");
		return;
	}

	std::vector<std::string> targets = split(msg.params[0], ',');
	for (size_t i = 0; i < targets.size(); ++i)
	{
		const std::string &target = targets[i];

		if (target.empty())
			continue;
		if (target[0] == '#')
		{
			Channel *channel = findChannel(target);

			if (channel == NULL)
			{
				if (!notice)
					reply(client, "403", target + " :No such channel");
				continue;
			}
			if (!channel->hasMember(&client))
			{
				if (!notice)
					reply(client, "404", channel->getName() + " :Cannot send to channel");
				continue;
			}
			channel->broadcast(":" + client.prefix() + " " + command + " " + channel->getName()
				+ " :" + msg.params[1], &client);
		}
		else
		{
			Client *dest = findClient(target);

			if (dest == NULL || !dest->isRegistered())
			{
				if (!notice)
					reply(client, "401", target + " :No such nick/channel");
				continue;
			}
			dest->queue(":" + client.prefix() + " " + command + " " + dest->getNick() + " :" + msg.params[1]);
		}
	}
}
