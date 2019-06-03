/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:23:45 by kmira             #+#    #+#             */
/*   Updated: 2019/06/02 19:40:15 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		ls_recurse_into(char const *argv, t_flag_bit *flags)
{
	t_file_tree	*head;

	if (*flags & FLAG_FIRST_CALL)
		*flags = *flags ^ FLAG_FIRST_CALL;
	head = create_tree(argv, *flags);
	tree_traversal(head, *flags);
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
