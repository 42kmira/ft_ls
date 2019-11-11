/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:43:32 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 14:30:37 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

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

void	print_size(char *size, int padd_amount)
{
	char	*padded_size;

	padded_size = padded_number(size, padd_amount);
	buffer_output_str(padded_size, 0);
	free(padded_size);
}

void	print_directory_header(t_inode *directory, t_h_output *h_output)
{
	if (h_output->newline == 1)
		buffer_output_str("\n", 0);
	else
		h_output->newline = 1;
	if (h_output->only_dir == 0)
	{
		if (*h_output->flags & c_FLAG)
			buffer_output_str(directory->color, 0);
		buffer_output_str(directory->file_name, 0);
		if (*h_output->flags & c_FLAG)
			buffer_output_str(COLOR_RESET, 0);
		buffer_output_str(":\n", 0);
	}
}
