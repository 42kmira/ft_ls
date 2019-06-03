/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:23:45 by kmira             #+#    #+#             */
/*   Updated: 2019/06/03 02:28:23 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

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

void		ls_recurse_into(char const *directory_path, t_flag_bit *flags)
{
	t_file_tree	*head;

	if (*flags & FLAG_FIRST_CALL)
		*flags = *flags ^ FLAG_FIRST_CALL;
	head = create_tree(directory_path, *flags);
	tree_traversal(head, *flags, directory_path);
	tree_recursion(head, flags);
	free_tree(head);
}

void		ls_main(const char *file, t_flag_bit *flags)
{
	if (!(*flags & FLAG_FIRST_CALL))
		write(1, "\n", 1);
	printf("%s:\n", file);
	ls_recurse_into(file, flags);
}
