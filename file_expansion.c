/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:11:33 by kmira             #+#    #+#             */
/*   Updated: 2019/06/02 19:21:01 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		insert_to_tree_structure(t_file_tree *root, struct dirent *file, char const *directory_path)
{
	if (ft_strcmp(root->d_name, file->d_name) >= 0)
	{
		if (root->smaller == NULL)
		{
			root->smaller = malloc(sizeof(*(root->smaller)));
			ft_strcpy(root->smaller->d_name, file->d_name);
			ft_bzero(root->smaller->path_name, sizeof(MAXNAMLEN));
			concat_file_to_directory(root->smaller->path_name, file->d_name, directory_path);
			root->smaller->smaller = NULL;
			root->smaller->greater = NULL;
		}
		else
			insert_to_tree_structure(root->smaller, file, directory_path);
	}
	else
	{
		if (root->greater == NULL)
		{
			root->greater = malloc(sizeof(*(root->greater)));
			ft_strcpy(root->greater->d_name, file->d_name);
			ft_bzero(root->greater->path_name, sizeof(MAXNAMLEN));
			concat_file_to_directory(root->greater->path_name, file->d_name, directory_path);
			root->greater->smaller = NULL;
			root->greater->greater = NULL;
		}
		else
			insert_to_tree_structure(root->greater, file, directory_path);
	}
}

t_file_tree	*create_tree(char const *directory_path, t_flag_bit flags)
{
	t_file_tree		*head;
	struct dirent	*file;
	DIR				*directory;

	directory = opendir(directory_path);
	file = readdir(directory);
	head = malloc(sizeof(*head));
	ft_bzero(head->path_name, MAXNAMLEN);

	concat_file_to_directory(head->path_name, file->d_name, directory_path);
	head->greater = NULL;
	head->smaller = NULL;
	ft_strcpy(head->d_name, file->d_name);
	file = readdir(directory);
	while (file)
	{
		if ((file->d_name[0] != '.') || (flags & FLAG_a))
			insert_to_tree_structure(head, file, directory_path);
		file = readdir(directory);
	}
	closedir(directory);
	return (head);
}

void		tree_traversal(t_file_tree *root, t_flag_bit flags)
{
	if (root != NULL)
	{
		if (root->smaller != NULL)
			tree_traversal(root->smaller, flags);
		print_file(root->d_name, flags);
		if (root->greater != NULL)
			tree_traversal(root->greater, flags);
	}
}

void		tree_recursion(t_file_tree *root, t_flag_bit *flags)
{
	struct stat info;

	ft_bzero(&info, sizeof(info));
	if (root != NULL)
	{
		if (root->smaller != NULL)
			tree_recursion(root->smaller, flags);
		stat(root->path_name, &info);
		if (*flags & FLAG_R && S_ISDIR(info.st_mode))
			if (root->d_name[0] != '.' || (root->d_name[0] != '.' && root->d_name[1] != '.'))
				ls_main(root->path_name, flags);
		if (root->greater != NULL)
			tree_recursion(root->greater, flags);
	}
}

void		free_tree(t_file_tree *root)
{
	if (root != NULL)
	{
		if (root->smaller != NULL)
		{
			ft_bzero(root->d_name, sizeof(root->d_name));
			ft_bzero(root->path_name, sizeof(root->path_name));
			free_tree(root->smaller);
			root->smaller = NULL;
		}
		if (root->greater != NULL)
		{
			ft_bzero(root->d_name, sizeof(root->d_name));
			ft_bzero(root->path_name, sizeof(root->path_name));
			free_tree(root->greater);
			root->greater = NULL;
		}
		free(root);
		root = NULL;
	}
}
