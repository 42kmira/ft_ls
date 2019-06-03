/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:11:33 by kmira             #+#    #+#             */
/*   Updated: 2019/06/02 20:00:44 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file_tree	*create_file_node(char const *file_name, char const *directory_path)
{
	t_file_tree *result;

	result = malloc(sizeof(*result));
	ft_bzero(result, sizeof(*result));
	ft_strcpy(result->d_name, file_name);
	concat_file_to_directory(result->path_name, file_name, directory_path);
	result->smaller = NULL;
	result->greater = NULL;
	return (result);
}

void		insert_to_tree_structure
	(t_file_tree *root, struct dirent *file, char const *directory_path)
{
	if (ft_strcmp(root->d_name, file->d_name) >= 0)
	{
		if (root->smaller == NULL)
			root->smaller = create_file_node(file->d_name, directory_path);
		else
			insert_to_tree_structure(root->smaller, file, directory_path);
	}
	else
	{
		if (root->greater == NULL)
			root->greater = create_file_node(file->d_name, directory_path);
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
	head = create_file_node(file->d_name, directory_path);
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
