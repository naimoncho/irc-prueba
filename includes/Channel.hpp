/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:30:53 by ncheniou          #+#    #+#             */
/*   Updated: 2026/11/11 09:32:40 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>
# include <ctime>

class Client;

class Channel
{
	public:
		explicit Channel(const std::string &name);
		~Channel();

		const std::string			&getName() const;
		std::time_t					getCreationTime() const;

		const std::string			&getTopic() const;
		void						setTopic(const std::string &topic);

		// ---- members ----
		const std::set<Client *>	&getMembers() const;
		bool						hasMember(Client *client) const;
		bool						isOperator(Client *client) const;
		bool						isEmpty() const;
		void						addMember(Client *client);
		void						removeMember(Client *client);
		void						setOperator(Client *client, bool on);

		// ---- modes ----
		bool						isInviteOnly() const;
		void						setInviteOnly(bool on);
		bool						isTopicRestricted() const;
		void						setTopicRestricted(bool on);
		const std::string			&getKey() const;
		void						setKey(const std::string &key);
		size_t						getLimit() const;
		void						setLimit(size_t limit);
		bool						isFull() const;

		bool						isInvited(Client *client) const;
		void						addInvite(Client *client);

		void						broadcast(const std::string &line, Client *except = NULL) const;
		
		std::string					namesList() const;

		std::string					modeString(bool showKey) const;

	private:
		Channel();
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);

		std::string			_name;
		std::string			_topic;
		std::string			_key;
		size_t				_limit;
		bool				_inviteOnly;
		bool				_topicRestricted;
		std::time_t			_created;
		std::set<Client *>	_members;
		std::set<Client *>	_operators;
		std::set<Client *>	_invited;
};

#endif
