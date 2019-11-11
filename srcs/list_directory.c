/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 23:10:59 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 14:22:47 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

char	is_hidden(char *file_path)
{
	char	*delim;
	int		result;

	result = 0;
	delim = ft_strrchr(file_path, '/');
	if (delim == NULL)
	{
		if (file_path[0] == '.')
			result = 1;
	}
	else
	{
		if (delim[1] == '.')
			result = 1;
	}
	return (result);
}

void	handle_directory(t_inode *root,
		t_h_output *h_output, t_flag_mask *flags)
{
	DIR				*directory_stream;
	struct dirent	*inode;
	t_inode			*head;
	t_inode			*elem;
	int				total;

	while (root)
	{
		directory_stream = opendir(root->file_name);
		if (h_output->recurse_active == 1 && is_hidden(root->file_name))
			directory_stream = NULL;
		if (directory_stream != NULL)
		{
			head = NULL;
			total = 0;
			h_output->longest_size = 0;
			print_directory_header(root, h_output);
			while ((inode = readdir(directory_stream)))
			{
				if (inode->d_name[0] != '.' || (*flags & a_FLAG))
				{
					if (head == NULL)
						head = expand_from_path(inode->d_name, root->file_name);
					else
					{
						elem = expand_from_path(inode->d_name, root->file_name);
						total += elem->stat_info.st_blocks;
						insert_inode(head, elem, h_output);
						h_output->only_dir = 0;
						if (elem->size_length > h_output->longest_size)
							h_output->longest_size = elem->size_length;
					}
				}
			}
			if (head != NULL)
				total += head->stat_info.st_blocks;
			if (*h_output->flags & l_FLAG)
				print_total_blocks(total);
			closedir(directory_stream);
			print_tree_type(head, h_output, REG_FILE | DIRECTORY);
			if (*flags & R_FLAG)
			{
				h_output->recurse_active = 1;
				elem = extract_directories(head);
				handle_directory(elem, h_output, flags);
			}
			free_tree(head);
		}
		root = root->next;
	}
}
