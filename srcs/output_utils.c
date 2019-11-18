/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 00:07:46 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 00:52:01 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	init_h_output(t_h_output *h_output, t_flag_mask *flags)
{
	ft_bzero(h_output, sizeof(*h_output));
	h_output->only_dir = 1;
	h_output->recurse_active = 0;
	h_output->newline = 0;
	h_output->flags = flags;
	h_output->longest_size = 0;
	*h_output->flags = (*h_output->flags | c_FLAG);
	fetch_cmp_function(h_output);
}

void	zero_out_length_data(t_h_output *h_output)
{
	h_output->longest_size = 0;
	h_output->longest_nlinks = 0;
	h_output->longest_pw_name = 0;
	h_output->longest_gr_name = 0;
	h_output->total_block_size = 0;
}

void	find_longest_out_data(t_inode *root, t_h_output *h_output)
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
