/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:38:23 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 22:35:12 by kmira            ###   ########.fr       */
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

void	padd_string(int pad_length)
{
	int		i;
	char	*result;

	i = 0;
	if (pad_length <= 0)
		return ;
	result = malloc(sizeof(pad_length) + 1);
	result[pad_length] = '\0';
	while (i < pad_length)
	{
		result[i] = ' ';
		i = i + 1;
	}
	buffer_output_str(result, 0);
}

void	fill_long_print_info(t_inode *file)
{
	struct passwd	*user_info;
	struct group	*group_info;

	user_info = getpwuid(file->stat_info.st_uid);
	group_info = getgrgid(file->stat_info.st_gid);
	file->size = ft_itoa(file->stat_info.st_size);
	file->nlinks = ft_itoa(file->stat_info.st_nlink);
	file->pw_name = ft_strdup(user_info->pw_name);
	file->gr_name = ft_strdup(group_info->gr_name);
}

void	add_inode(t_inode **head, char *file_name,
				char *dir_name, t_h_output *h_output)
{
	t_inode			*elem;

	if (*head == NULL)
	{
		elem = expand_from_path(file_name, dir_name);
		*head = elem;
	}
	else
	{
		elem = expand_from_path(file_name, dir_name);
		insert_inode(*head, elem, h_output);
		h_output->only_dir = 0;
	}
	if (*h_output->flags & l_FLAG)
		fill_long_print_info(elem);
}
