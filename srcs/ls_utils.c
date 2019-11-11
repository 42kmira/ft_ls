/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:38:23 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 14:30:00 by kmira            ###   ########.fr       */
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

void	init_h_output(t_h_output *h_output, t_flag_mask *flags)
{
	ft_bzero(h_output, sizeof(*h_output));
	h_output->only_dir = 1;
	h_output->recurse_active = 0;
	h_output->newline = 0;
	h_output->flags = flags;
	h_output->longest_size = 0;
	*h_output->flags = (*h_output->flags | c_FLAG);
	if (*h_output->flags & t_FLAG)
	{
		h_output->comparator = &ls_time_cmp;
	}
	else
	{
		h_output->comparator = &ls_ascii_cmp;
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
