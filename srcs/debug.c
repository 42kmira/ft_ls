/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 02:22:59 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 00:10:20 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	short_print(t_h_output *h_output, t_inode *root)
{
	if (*h_output->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (*h_output->flags & c_FLAG)
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
