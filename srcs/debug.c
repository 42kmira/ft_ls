/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 02:22:59 by kmira             #+#    #+#             */
/*   Updated: 2019/11/10 16:40:09 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	short_print(t_h_output *output_handler, t_inode *root)
{
	if (*output_handler->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (*output_handler->flags & c_FLAG)
		buffer_output_str(COLOR_RESET, 0);
	buffer_output_str("\n", 0);
}

void	print_permissions(mode_t permission)
{
	char	buff[10];

	ft_memset(buff, '-', sizeof(buff));
	buff[9] = '\0';
	if (permission & S_IRUSR)
		buff[0] = 'r';
	if (permission & S_IWUSR)
		buff[1] = 'w';
	if (permission & S_IXUSR)
		buff[2] = 'x';
	if (permission & S_IRGRP)
		buff[3] = 'r';
	if (permission & S_IWGRP)
		buff[4] = 'w';
	if (permission & S_IXGRP)
		buff[5] = 'x';
	if (permission & S_IROTH)
		buff[6] = 'r';
	if (permission & S_IWOTH)
		buff[7] = 'w';
	if (permission & S_IXOTH)
		buff[8] = 'x';
	buffer_output_str(buff, 0);
	buffer_output_str("  ", 0);
}

void	long_print(t_h_output *output_handler, t_inode *root)
{
	struct passwd	*user_info;
	struct group	*group_info;

	user_info = getpwuid(root->stat_info.st_uid);
	group_info = getgrgid(root->stat_info.st_gid);
	if (*output_handler->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	if (root->type & DIRECTORY)
		buffer_output_str("d", 0);
	else
		buffer_output_str("-", 0);
	print_permissions(root->stat_info.st_mode);
	print_links(root->stat_info.st_nlink);
	buffer_output_str(" ", 0);
	buffer_output_str(user_info->pw_name, 0);
	buffer_output_str("  ", 0);
	buffer_output_str(group_info->gr_name, 0);
	buffer_output_str("  ", 0);
	print_size(root->size, output_handler->longest_size + 2);
	print_time(&root->stat_info.st_mtimespec);
	buffer_output_str(" ", 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (*output_handler->flags & c_FLAG)
		buffer_output_str(COLOR_RESET, 0);
	buffer_output_str("\n", 0);
}

void	print_tree(t_inode *root)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		print_tree(root->left);
	if (root->right != NULL)
		print_tree(root->right);
}

void	print_tree_type(t_inode *root, t_h_output *output_handler,
						t_inode_type mask)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		print_tree_type(root->left, output_handler, mask);
	if (root->type & mask)
	{
		if (*output_handler->flags & l_FLAG && !(root->type & BAD_FILE))
			long_print(output_handler, root);
		else
			short_print(output_handler, root);
		output_handler->only_dir = 0;
		output_handler->newline = 1;
	}
	if (root->right != NULL)
		print_tree_type(root->right, output_handler, mask);
}
