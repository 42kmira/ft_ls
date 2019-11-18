/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 23:10:59 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 00:34:44 by kmira            ###   ########.fr       */
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

	while (root)
	{
		directory_stream = opendir(root->file_name);
		if (h_output->recurse_active == 1 && is_hidden(root->file_name))
			directory_stream = NULL;
		print_directory_header(root, h_output);
		if (directory_stream != NULL)
		{
			head = NULL;
			while ((inode = readdir(directory_stream)))
				if (inode->d_name[0] != '.' || (*flags & a_FLAG))
					create_inode(&head, inode->d_name, root->file_name, h_output);
			closedir(directory_stream);
			if (*h_output->flags & l_FLAG)
			{
				zero_out_length_data(h_output);
				find_longest_out_data(head, h_output);
				print_total_blocks(h_output->total_block_size);
			}
			print_tree_type(head, h_output, ~(HIDDEN_FILE) | HIDDEN_FILE);
			if (*flags & R_FLAG)
			{
				h_output->recurse_active = 1;
				handle_directory(extract_directories(head), h_output, flags);
			}
			free_tree(head);
		}
		else
			error_cannot_open_file(root->file_name);
		root = root->next;
	}
}
