/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 01:24:57 by kmira             #+#    #+#             */
/*   Updated: 2019/11/10 15:49:09 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	insert_inode(t_inode *root, t_inode *node, t_h_output *output_handler)
{
	int	direction;

	direction = ls_master_cmp(root, node, output_handler);
	if (direction == LEFT_NODE)
	{
		if (root->left == NULL)
			root->left = node;
		else
			insert_inode(root->left, node, output_handler);
	}
	if (direction == RIGHT_NODE)
	{
		if (root->right == NULL)
			root->right = node;
		else
			insert_inode(root->right, node, output_handler);
	}
}

t_inode	*expand_from_path(char *file_name, char *dir_name)
{
	int		status;
	t_inode	*file;

	file = malloc(sizeof(*file));
	create_file_name(file, dir_name, file_name);
	status = stat(file->file_name, &file->stat_info);
	if (status == -1)
		error_stat(file);
	if (S_ISREG(file->stat_info.st_mode))
	{
		file->type = REG_FILE;
		file->color = BOLDLIGHT_PURPLE;
		if (S_IXUSR & file->stat_info.st_mode)
			file->color = BOLDCYAN;
	}
	else if (S_ISDIR(file->stat_info.st_mode))
	{
		file->type = DIRECTORY;
		file->color = BOLDPURPLE;
	}
	file->size = ft_itoa(file->stat_info.st_size);
	file->size_length = ft_strlen(file->size);
	file->right = NULL;
	file->left = NULL;
	file->next = NULL;
	return (file);
}

void	list_directory(t_inode **starting, t_inode *node)
{
	t_inode	*iter;

	iter = *starting;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = node;
}

void	extract_algo(t_inode *root, t_inode **starting)
{
	if (root->left != NULL)
		extract_algo(root->left, starting);
	if (root->type & DIRECTORY)
	{
		if (*starting == NULL)
			*starting = root;
		else
			list_directory(starting, root);
	}
	if (root->right != NULL)
		extract_algo(root->right, starting);
}

t_inode	*extract_directories(t_inode *root)
{
	t_inode	*starting;

	starting = NULL;
	if (root != NULL)
		extract_algo(root, &starting);
	return (starting);
}

t_inode	*get_inodes_from_args(char **args, t_h_output *output_handler)
{
	size_t		i;
	t_inode		*head;
	t_inode		*elem;

	i = -1;
	head = NULL;
	if (args[0] != NULL)
	{
		output_handler->longest_size = 0;
		while (args[++i] != NULL)
			if (head == NULL)
				head = expand_from_path(args[i], "");
			else
			{
				elem = expand_from_path(args[i], "");
				insert_inode(head, elem, output_handler);
				if (elem->size_length > output_handler->longest_size)
					output_handler->longest_size = elem->size_length;
				output_handler->only_dir = 0;
			}
		print_tree_type(head, output_handler, BAD_FILE | REG_FILE);
	}
	else if (args[i] == NULL)
		head = expand_from_path(".", "");
	return (head);
}
