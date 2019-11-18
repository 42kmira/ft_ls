/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_inodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 05:42:12 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 05:42:15 by kmira            ###   ########.fr       */
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

static void	create_file_name(t_inode *inode, char *dir_name, char *file_name)
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

void		add_inode(t_inode **head, char *file_name,
				char *dir_name, t_h_output *h_output)
{
	t_inode			*elem;
	struct passwd	*user_info;
	struct group	*group_info;

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
	{
		user_info = getpwuid(elem->stat_info.st_uid);
		group_info = getgrgid(elem->stat_info.st_gid);
		elem->size = ft_itoa(elem->stat_info.st_size);
		elem->nlinks = ft_itoa(elem->stat_info.st_nlink);
		elem->pw_name = ft_strdup(user_info->pw_name);
		elem->gr_name = ft_strdup(group_info->gr_name);
	}
}
