/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:27:05 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 14:30:01 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

#define BUFFER 4096

void	buffer_output_str(char *str, int final)
{
	static char		buff[BUFFER];
	static int		location;
	size_t			i;
	size_t			length;

	i = 0;
	length = ft_strlen(str);
	while (i < length)
	{
		if (location == BUFFER)
		{
			write(1, buff, location);
			ft_bzero(buff, BUFFER);
			location = 0;
		}
		buff[location++] = str[i++];
	}
	if (final == 1 && location != 0)
	{
		write(1, buff, location);
		ft_bzero(buff, BUFFER);
		location = 0;
	}
}

void	flush_buffer_str(void)
{
	char str[0];

	str[0] = '\0';
	buffer_output_str(str, 1);
}
