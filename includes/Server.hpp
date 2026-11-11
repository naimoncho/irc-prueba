/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:31:07 by ncheniou          #+#    #+#             */
/*   Updated: 2026/11/11 09:33:49 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <vector>
# include <map>
# include <csignal>
# include <poll.h>

# include "Client.hpp"
# include "Channel.hpp"
# include "Message.hpp"

# define SERVER_NAME "ircserv"

class Server
{
	public:
		Server(int port, const std::string &password);
		~Server();

		void		run();
		static void	stop();

	private:
		Server();
		Server(const Server &other);
		Server &operator=(const Server &other);

		typedef void (Server::*Handler)(Client &, const Message &);

		void	setupListener(int port);
		void	buildPollFds(std::vector<struct pollfd> &fds) const;
		void	acceptClient();
		void	handleRead(Client &client);
		void	handleWrite(Client &client);
		void	disconnect(Client &client, const std::string &reason, bool flush);
		void	reapClients();
		void	execute(Client &client, const std::string &line);

		void	reply(Client &client, const std::string &code, const std::string &text) const;
		Client	*findClient(const std::string &nick) const;
		Channel	*findChannel(const std::string &name) const;
		void	leaveChannel(Client &client, Channel *channel);
		void	broadcastToPeers(Client &client, const std::string &line, bool includeSelf) const;

		void	cmdCap(Client &client, const Message &msg);
		void	cmdPass(Client &client, const Message &msg);
		void	cmdNick(Client &client, const Message &msg);
		void	cmdUser(Client &client, const Message &msg);
		void	cmdPing(Client &client, const Message &msg);
		void	cmdPong(Client &client, const Message &msg);
		void	cmdQuit(Client &client, const Message &msg);
		void	tryRegister(Client &client);

		void	cmdJoin(Client &client, const Message &msg);
		void	cmdPart(Client &client, const Message &msg);
		void	cmdTopic(Client &client, const Message &msg);
		void	cmdNames(Client &client, const Message &msg);
		void	cmdWho(Client &client, const Message &msg);
		void	joinChannel(Client &client, const std::string &name, const std::string &key);
		void	sendNames(Client &client, const Channel &channel) const;

		void	cmdPrivmsg(Client &client, const Message &msg);
		void	cmdNotice(Client &client, const Message &msg);
		void	relay(Client &client, const Message &msg, bool notice);

		void	cmdKick(Client &client, const Message &msg);
		void	cmdInvite(Client &client, const Message &msg);

		void	cmdMode(Client &client, const Message &msg);
		void	applyChannelModes(Client &client, Channel &channel, const Message &msg);

		int								_listenFd;
		std::string						_password;
		std::map<int, Client *>			_clients;
		std::map<std::string, Channel *>	_channels;
		std::map<std::string, Handler>	_handlers;

		static volatile sig_atomic_t	_stop;
};

#endif
