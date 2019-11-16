/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 21:45:46 by kmira             #+#    #+#             */
/*   Updated: 2019/11/16 01:35:13 by kmira            ###   ########.fr       */
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

int		ls_no_cmp(t_inode *a __attribute__((unused)), t_inode *b __attribute__((unused)))
{
	// printf("FILE: %s", a->file_name);
	if (b->file_name[b->file_loc] == '.' || a->file_name[a->file_loc] == '.')
	{
		if (a->file_name[a->file_loc + 1] == '\0')
			return (LEFT_NODE);
		if (b->file_name[b->file_loc + 1] == '\0')
			return (LEFT_NODE);
		if (a->file_name[a->file_loc + 1] == '.')
			return (LEFT_NODE);
		if (b->file_name[b->file_loc + 1] == '.')
			return (LEFT_NODE);
	}
	return (RIGHT_NODE);
}

int		ls_size_cmp(t_inode *a, t_inode *b)
{
	int result;

	result = b->stat_info.st_size - a->stat_info.st_size;
	if (result > 0)
		return (LEFT_NODE);
	else if (result < 0)
		return (RIGHT_NODE);
	else
		return (ls_ascii_cmp(a, b));
}

int		ls_mtime_cmp(t_inode *a, t_inode *b)
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

/*
** The u flag does not affect sorting at all. Instead it affects
** what will be printed when using the -l flag.
*/

int		ls_atime_cmp(t_inode *a, t_inode *b)
{
	return (ls_ascii_cmp(a, b));
}

int		ls_master_cmp(t_inode *a, t_inode *b, t_h_output *h_output)
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
		result = h_output->comparator(a, b);
	if (a->type & BAD_FILE || b->type & BAD_FILE)
		return (result);
	if (*h_output->flags & r_FLAG)
	{
		if (result == 0)
			return (RIGHT_NODE);
		else
			return (result * -1);
	}
	return (result);
}
