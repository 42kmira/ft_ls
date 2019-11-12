/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:35:43 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 22:55:45 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

/*
**	printf("%s: illegal option -- %c\n", name, bad_key);
*/

void	error_bad_flag(char bad_key)
{
	char	*name;

	name = program_name(FETCH_NAME);
	write(1, name, ft_strlen(name));
	write(1, ": illegal option -- ", 20);
	write(1, &bad_key, 1);
	write(1, "\n", 1);
	error_ls_usage();
}

void	error_ls_usage(void)
{
	char	*name;

	name = program_name(FETCH_NAME);
	write(1, "usage: ", 8);
	write(1, name, ft_strlen(name));
	write(1, " [-Ralrt] [file ...]\n", 22);
}

void	error_stat(t_inode *file)
{
	if (errno == ENOENT)
	{
		file->type = BAD_FILE;
		ft_strcpy(&file->file_name[ft_strlen(file->file_name)],
		COLOR_RESET": file does not exist");
		file->color = BOLDRED;
		errno &= ~(ENOENT);
	}
	else
		buffer_output_str("stat() failed seriously", 0);
}
