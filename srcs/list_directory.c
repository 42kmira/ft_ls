/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 23:10:59 by kmira             #+#    #+#             */
/*   Updated: 2019/11/10 15:05:13 by kmira            ###   ########.fr       */
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

void	handle_directory(t_inode *root, t_h_output *output_handler, t_flag_mask *flags)
{
	DIR				*directory_stream;
	struct dirent	*inode;
	t_inode			*head;
	t_inode			*elem;
	int				total;

	while (root)
	{
		directory_stream = opendir(root->file_name);
		if (output_handler->recurse_active == 1 && is_hidden(root->file_name))
			directory_stream = NULL;
		if (directory_stream != NULL)
		{
			head = NULL;
			total = 0;
			output_handler->longest_size = 0;
			print_directory_header(root, output_handler);
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
						insert_inode(head, elem, output_handler);
						output_handler->only_dir = 0;
						if (elem->size_length > output_handler->longest_size)
							output_handler->longest_size = elem->size_length;
					}
				}
			}
			if (head != NULL)
				total += head->stat_info.st_blocks;
			if (*output_handler->flags & l_FLAG)
				print_total_blocks(total);
			closedir(directory_stream);
			print_tree_type(head, output_handler, REG_FILE | DIRECTORY);
			if (*flags & R_FLAG)
			{
				output_handler->recurse_active = 1;
				elem = extract_directories(head);
				handle_directory(elem, output_handler, flags);
			}
			free_tree(head);
		}
		root = root->next;
	}
}
