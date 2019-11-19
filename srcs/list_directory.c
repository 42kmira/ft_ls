/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 23:10:59 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 16:48:26 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

static char			is_hidden(char *file_path)
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

/*
** This function prepares things for the long format printing.
** This is done by clearing out the previous recorded data,
** traversing the tree and recording the longest sequences
** and then printing out:
** total <blocks>
** that appears when using the l_FLAG, '-l'.
*/

inline static void	l_directory_protocal(t_h_output *h_output, t_inode *head)
{
	if (*h_output->flags & l_FLAG)
	{
		zero_out_length_data(h_output);
		find_longest_out_data(head, h_output);
		print_total_blocks(h_output->total_block_size);
	}
}

static DIR			*fetch_directory(char *file_name, t_h_output *h_output)
{
	DIR				*directory_stream;

	directory_stream = opendir(file_name);
	if (h_output->recurse_active == 1 && is_hidden(file_name))
		directory_stream = NULL;
	return (directory_stream);
}

void				handle_directory(t_inode *root, t_h_output *h_output,
									t_flag_mask *flags)
{
	DIR				*directory_stream;
	struct dirent	*dirent;
	t_inode			*head;

	while (root)
	{
		directory_stream = fetch_directory(root->file_name, h_output);
		print_directory_header(root, h_output);
		if (directory_stream != NULL)
		{
			head = NULL;
			while ((dirent = readdir(directory_stream)))
				if (dirent->d_name[0] != '.' || (*flags & a_FLAG))
					add_inode(&head, dirent->d_name, root->file_name, h_output);
			closedir(directory_stream);
			l_directory_protocal(h_output, head);
			print_tree(head, h_output, ~(HIDDEN_FILE) | HIDDEN_FILE);
			if (*flags & R_FLAG && (h_output->recurse_active = 1))
				handle_directory(extract_directories(head), h_output, flags);
			free_tree(head);
		}
		else if (is_hidden(root->file_name) != 1)
			error_cannot_open_file(&root->file_name[root->file_loc]);
		root = root->next;
	}
}
