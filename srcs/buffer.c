/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:27:05 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 16:28:34 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

#define BUFFER_SIZE 4096

/*
** This allows the program to be buffered in
** static char buff[BUFFER_SIZE]. Once this memory spot is at capacity
** a call to write to done. A string is passed and if in the middle of
** that string the buffer is at capacity a call to write is done,
** but the index of string is kept. The index `location`
** is reset and the buffer continues to be written.
** This function can also be forcefully flushed out by provided the
** value 1 to int final.
** A wrapper function that flushes the buffer out is provided below.
*/

void	buffer_output_str(char *str, int final)
{
	static char		buff[BUFFER_SIZE];
	static int		location;
	size_t			length;
	size_t			i;

	i = 0;
	length = ft_strlen(str);
	while (i < length)
	{
		if (location == BUFFER_SIZE)
		{
			write(1, buff, location);
			ft_bzero(buff, BUFFER_SIZE);
			location = 0;
		}
		buff[location] = str[i];
		location++;
		i++;
	}
	if (final == 1 && location != 0)
	{
		write(1, buff, location);
		ft_bzero(buff, BUFFER_SIZE);
		location = 0;
	}
}

void	flush_buffer_str(void)
{
	char str[0];

	str[0] = '\0';
	buffer_output_str(str, 1);
}
