/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:30:59 by ncheniou          #+#    #+#             */
/*   Updated: 2026/11/11 09:32:56 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <ctime>

class Client
{
	public:
		Client(int fd, const std::string &host);
		~Client();

		int					getFd() const;
		const std::string	&getHost() const;
		const std::string	&getNick() const;
		const std::string	&getUser() const;
		const std::string	&getRealName() const;

		std::string			prefix() const;

		void				setNick(const std::string &nick);
		void				setUser(const std::string &user, const std::string &real);

		bool				hasPassword() const;
		void				setPassword(bool ok);
		bool				isRegistered() const;
		void				setRegistered();

		std::string			&inBuf();
		std::string			&outBuf();

		void				queue(const std::string &line);
		bool				hasPendingOutput() const;
		bool				hasOverflowed() const;

		bool				isClosing() const;
		bool				isDead() const;
		bool				isGone() const;
		void				setClosing(std::time_t deadline);
		void				setDead();
		std::time_t			getDeadline() const;

	private:
		Client();
		Client(const Client &other);
		Client &operator=(const Client &other);

		int			_fd;
		std::string	_host;
		std::string	_nick;
		std::string	_user;
		std::string	_real;
		std::string	_in;
		std::string	_out;
		bool		_password;
		bool		_registered;
		bool		_closing;
		bool		_dead;
		bool		_overflow;
		std::time_t	_deadline;
};

#endif
