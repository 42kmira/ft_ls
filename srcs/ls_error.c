/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:35:43 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 16:56:24 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

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
	write(1, " [-RSUacflrtu1] [file ...]\n", 28);
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

void	error_cannot_open_file(char *file_name)
{
	char *name;
	char *temp;

	name = program_name(FETCH_NAME);
	temp = ft_strrchr(file_name, '/');
	if (temp != NULL)
		file_name = temp + 1;
	if (errno == EACCES)
	{
		buffer_output_str(name, 0);
		buffer_output_str(": ", 0);
		buffer_output_str(file_name, 0);
		buffer_output_str(": Permission denied\n", 0);
		errno &= ~(EACCES);
	}
	else
		buffer_output_str("Some other error opening the file.\n", 0);
}
