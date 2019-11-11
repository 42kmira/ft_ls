/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 21:45:46 by kmira             #+#    #+#             */
/*   Updated: 2019/11/10 16:37:34 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

int		ls_ascii_cmp(t_inode *a, t_inode *b)
{
	int result;

	result = strcmp(a->file_name, b->file_name);
	if (result > 0)
		return (LEFT_NODE);
	else if (result < 0)
		return (RIGHT_NODE);
	else
		return (LEFT_NODE);
}

int		ls_time_cmp(t_inode *a, t_inode *b)
{
	struct timespec	a_time;
	struct timespec	b_time;

	a_time = a->stat_info.st_mtimespec;
	b_time = b->stat_info.st_mtimespec;
	if (a_time.tv_sec < b_time.tv_sec)
		return (LEFT_NODE);
	else if (a_time.tv_sec > b_time.tv_sec)
		return (RIGHT_NODE);
	else if (a_time.tv_nsec < b_time.tv_nsec)
		return (LEFT_NODE);
	else if (a_time.tv_nsec > b_time.tv_nsec)
		return (RIGHT_NODE);
	else
		return (ls_ascii_cmp(a, b));
}

int		ls_master_cmp(t_inode *a, t_inode *b, t_h_output *output_handler)
{
	int result;

	result = 0;
	if (a->type == BAD_FILE && b->type == BAD_FILE)
		result = ls_ascii_cmp(a, b);
	else if (a->type == BAD_FILE)
		result = RIGHT_NODE;
	else if (b->type == BAD_FILE)
		result = LEFT_NODE;
	else
		result = output_handler->comparator(a, b);
	if (a->type & BAD_FILE || b->type & BAD_FILE)
		return (result);
	if (*output_handler->flags & r_FLAG)
	{
		if (result == 0)
			return (RIGHT_NODE);
		else
			return (result * -1);
	}
	return (result);
}
