/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 01:24:57 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 15:30:02 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void		extract_algo(t_inode *root, t_inode **starting)
{
	t_inode	*iter;

	if (root->left != NULL)
		extract_algo(root->left, starting);
	if (root->type & DIRECTORY)
	{
		if (*starting == NULL)
			*starting = root;
		else
		{
			iter = *starting;
			while (iter->next != NULL)
				iter = iter->next;
			iter->next = root;
		}
	}
	if (root->right != NULL)
		extract_algo(root->right, starting);
}

t_inode		*extract_directories(t_inode *root)
{
	t_inode	*starting;

	starting = NULL;
	if (root != NULL)
		extract_algo(root, &starting);
	return (starting);
}

t_inode		*get_inodes_from_args(char **args, t_h_output *h_output)
{
	size_t		i;
	t_inode		*head;

	i = -1;
	head = NULL;
	if (args[0] != NULL)
	{
		h_output->longest_size = 0;
		while (args[++i] != NULL)
			add_inode(&head, args[i], "", h_output);
		if (*h_output->flags & l_FLAG)
		{
			zero_out_length_data(h_output);
			find_longest_out_data(head, h_output);
		}
		print_tree(head, h_output, ~(DIRECTORY));
	}
	else if (args[i + 1] == NULL)
		head = expand_from_path(".", "");
	return (head);
}
