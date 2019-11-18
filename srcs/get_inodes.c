/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 01:24:57 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 00:01:34 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void		insert_inode(t_inode *root, t_inode *node, t_h_output *h_output)
{
	int	direction;

	direction = ls_master_cmp(root, node, h_output);
	if (direction == LEFT_NODE)
	{
		if (root->left == NULL)
			root->left = node;
		else
			insert_inode(root->left, node, h_output);
	}
	if (direction == RIGHT_NODE)
	{
		if (root->right == NULL)
			root->right = node;
		else
			insert_inode(root->right, node, h_output);
	}
}

static void	fill_info(t_inode *file)
{
	int i;

	i = 0;
	while (g_type_table[i].key != 0)
	{
		if (((file->stat_info.st_mode) & S_IFMT) == g_type_table[i].key)
		{
			file->type = g_type_table[i].type;
			file->color = g_type_table[i].color;
			file->type_letter[0] = g_type_table[i].letter;
		}
		i++;
	}
}

t_inode		*expand_from_path(char *file_name, char *dir_name)
{
	int		status;
	t_inode	*file;

	file = malloc(sizeof(*file));
	create_file_name(file, dir_name, file_name);
	status = lstat(file->file_name, &file->stat_info);
	if (status != 0)
	{
		if (status != 0)
			error_stat(file);
	}
	fill_info(file);
	if (S_IXUSR & file->stat_info.st_mode
		&& S_ISREG(file->stat_info.st_mode))
		file->color = BOLDCYAN;
	file->type_letter[1] = '\0';
	file->right = NULL;
	file->left = NULL;
	file->next = NULL;
	return (file);
}

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

void		find_longest_out_data(t_inode *root, t_h_output *h_output)
{
	int	length_nlinks;
	int	length_size;
	int	length_pw_name;
	int	length_gr_name;

	if (root == NULL)
		return ;
	if (root->left != NULL)
		find_longest_out_data(root->left, h_output);
	length_size = ft_strlen(root->size);
	length_nlinks = ft_strlen(root->nlinks);
	length_pw_name = ft_strlen(root->pw_name);
	length_gr_name = ft_strlen(root->gr_name);
	if (h_output->longest_size < length_size)
		h_output->longest_size = length_size;
	if (h_output->longest_nlinks < length_nlinks)
		h_output->longest_nlinks = length_nlinks;
	if (h_output->longest_pw_name < length_pw_name)
		h_output->longest_pw_name = length_pw_name;
	if (h_output->longest_gr_name < length_gr_name)
		h_output->longest_gr_name = length_gr_name;
	if (root->right != NULL)
		find_longest_out_data(root->right, h_output);
	h_output->total_block_size += root->stat_info.st_blocks;
}

void		zero_out_length_data(t_h_output *h_output)
{
	h_output->longest_size = 0;
	h_output->longest_nlinks = 0;
	h_output->longest_pw_name = 0;
	h_output->longest_gr_name = 0;
	h_output->total_block_size = 0;
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
		print_tree_type(head, h_output, ~(DIRECTORY));
	}
	else if (args[i + 1] == NULL)
		head = expand_from_path(".", "");
	return (head);
}
