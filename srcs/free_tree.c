/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 02:17:23 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 16:10:56 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

void	free_tree(t_inode *root)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		free_tree(root->left);
	if (root->right != NULL)
		free_tree(root->right);
	free(root->size);
	free(root->nlinks);
	free(root->pw_name);
	free(root->gr_name);
	free(root);
}
