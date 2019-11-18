/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:43:32 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 06:10:35 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	print_total_blocks(int total)
{
	char	*number;

	number = ft_itoa(total);
	buffer_output_str("total ", 0);
	buffer_output_str(number, 0);
	buffer_output_str("\n", 0);
	free(number);
}

void	print_directory_header(t_inode *directory, t_h_output *h_output)
{
	if (h_output->newline == 1)
		buffer_output_str("\n", 0);
	else
		h_output->newline = 1;
	if (h_output->only_dir == 0)
	{
		if (*h_output->flags & c_FLAG)
			buffer_output_str(directory->color, 0);
		buffer_output_str(directory->file_name, 0);
		if (*h_output->flags & c_FLAG)
			buffer_output_str(COLOR_RESET, 0);
		buffer_output_str(":\n", 0);
	}
}

void	print_tree_type(t_inode *root, t_h_output *h_output,
						t_inode_type mask)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		print_tree_type(root->left, h_output, mask);
	if (root->type & mask)
	{
		if (*h_output->flags & l_FLAG && !(root->type & BAD_FILE))
			long_print(h_output, root);
		else
			short_print(h_output, root);
		h_output->only_dir = 0;
		h_output->newline = 1;
	}
	if (root->right != NULL)
		print_tree_type(root->right, h_output, mask);
}

void	short_print(t_h_output *h_output, t_inode *root)
{
	if (*h_output->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (*h_output->flags & c_FLAG)
		buffer_output_str(COLOR_RESET, 0);
	buffer_output_str("\n", 0);
}

void	long_print(t_h_output *h_output, t_inode *root)
{
	char			*real_path;

	if (*h_output->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	buffer_output_str(root->type_letter, 0);
	print_permissions(root->stat_info.st_mode, root->file_name);
	print_links(root->nlinks, h_output->longest_nlinks + 1);
	print_pw_gr_names(root->pw_name, root->gr_name, h_output);
	print_size(root->size, h_output->longest_size + 2, root->stat_info);
	print_time(&root->stat_info, h_output);
	buffer_output_str(" ", 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (root->type & SYM_LINK)
	{
		buffer_output_str(" -> ", 0);
		real_path = ft_strnew(30);
		readlink(root->file_name, real_path, 30);
		buffer_output_str(real_path, 0);
	}
	if (*h_output->flags & c_FLAG)
		buffer_output_str(COLOR_RESET, 0);
	buffer_output_str("\n", 0);
}
