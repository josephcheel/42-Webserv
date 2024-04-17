/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_echo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:38:35 by eavedill          #+#    #+#             */
/*   Updated: 2024/04/17 22:27:17 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"

void str_echo (int sockfd)
{
	ssize_t	n;
	char	buf[MAXLINE];

	while ((n = Readn(sockfd, buf, MAXLINE)) > 0)
	{
		Writen(sockfd, buf, n);
		if (!(n < 0 && errno == EINTR))
			break;
	}
	if (n < 0)
		std::cerr << "str_Echo:read error\n";
	//err_sys("str_Echo:read error");
}
