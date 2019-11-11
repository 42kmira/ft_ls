/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:38:23 by kmira             #+#    #+#             */
/*   Updated: 2019/11/10 00:04:24 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

char	*program_name(char *arg_zero)
{
	static char *name;

	if (arg_zero != FETCH_NAME && name != NULL)
		ft_puterror("Error on program name: reassign to name.");
	if (arg_zero == FETCH_NAME && name == NULL)
		ft_puterror("Error on program name: name has not been assigned yet");
	if (name == NULL)
	{
		if (arg_zero[0] == '.' && arg_zero[1] == '/')
			name = &arg_zero[2];
		else
			name = arg_zero;
	}
	return (name);
}

void	init_h_output(t_h_output *output_handler, t_flag_mask *flags)
{
	ft_bzero(output_handler, sizeof(*output_handler));
	output_handler->only_dir = 1;
	output_handler->recurse_active = 0;
	output_handler->newline = 0;
	output_handler->flags = flags;
	output_handler->longest_size = 0;
	*output_handler->flags = (*output_handler->flags | c_FLAG);
	if (*output_handler->flags & t_FLAG)
	{
		output_handler->comparator = &ls_time_cmp;
	}
	else
	{
		output_handler->comparator = &ls_ascii_cmp;
	}
}

void	create_file_name(t_inode *inode, char *dir_name, char *file_name)
{
	inode->file_loc = ft_strlen(dir_name);
	ft_strcpy(inode->file_name, dir_name);
	if (inode->file_loc != 0)
	{
		inode->file_name[inode->file_loc] = '/';
		inode->file_loc = inode->file_loc + 1;
	}
	ft_strcpy(&inode->file_name[inode->file_loc], file_name);
}
