/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:43:32 by kmira             #+#    #+#             */
/*   Updated: 2019/11/10 16:32:16 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

#define BUFFER 4096

void	print_total_blocks(int total)
{
	char	*number;

	number = ft_itoa(total);
	buffer_output_str("total ", 0);
	buffer_output_str(number, 0);
	buffer_output_str("\n", 0);
	free(number);
}

void	print_time(struct timespec *time)
{
	char	time_string[26];

	ctime_r(&time->tv_sec, time_string);
	time_string[16] = '\0';
	buffer_output_str(&time_string[3], 0);
}

void	print_links(int links)
{
	char	*link_amount;

	link_amount = ft_itoa(links);
	buffer_output_str(link_amount, 0);
	free(link_amount);
}

char	*padded_number(char *num, int pad_length)
{
	int		space_length;
	int		i;
	char	*result;

	i = 0;
	result = malloc(sizeof(pad_length) + 1);
	space_length = pad_length - ft_strlen(num);
	while (i < space_length)
	{
		result[i] = ' ';
		i = i + 1;
	}
	ft_strcpy(&result[i], num);
	return (result);
}

void	print_size(char *size, int padd_amount)
{
	char	*padded_size;

	padded_size = padded_number(size, padd_amount);
	buffer_output_str(padded_size, 0);
	free(padded_size);
}

void	print_directory_header(t_inode *directory, t_h_output *output_handler)
{
	if (output_handler->newline == 1)
		buffer_output_str("\n", 0);
	else
		output_handler->newline = 1;
	if (output_handler->only_dir == 0)
	{
		if (*output_handler->flags & c_FLAG)
			buffer_output_str(directory->color, 0);
		buffer_output_str(directory->file_name, 0);
		if (*output_handler->flags & c_FLAG)
			buffer_output_str(COLOR_RESET, 0);
		buffer_output_str(":\n", 0);
	}
}

void	buffer_output(t_string *str, int final)
{
	static char		buff[BUFFER];
	static int		location;
	size_t			i;

	i = 0;
	while (i < str->length)
	{
		if (location == BUFFER)
		{
			write(1, buff, location);
			ft_bzero(buff, BUFFER);
			location = 0;
		}
		buff[location++] = str->ptr[i++];
	}
	if (final == 1 && location != 0)
	{
		write(1, buff, location);
		ft_bzero(buff, BUFFER);
		location = 0;
	}
}

void	flush_buffer(void)
{
	buffer_output(&(t_string){NULL, 0}, 1);
}

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
