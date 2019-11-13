/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:34:03 by kmira             #+#    #+#             */
/*   Updated: 2019/11/13 10:24:19 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

int		main(int aa __attribute__((unused)), char **args)
{
	size_t			at;
	t_flag_mask		flags;
	t_h_output		h_output;
	t_inode			*directories;
	t_inode			*head;

	at = 1;
	// program_name(args[0]);
	program_name("ls");
	flags = fetch_flags(&at, args);
	if ((flags & BAD_FLAG) == 0)
	{
		init_h_output(&h_output, &flags);
		head = get_inodes_from_args(&args[at], &h_output);
		directories = extract_directories(head);
		handle_directory(directories, &h_output, &flags);
		free_tree(head);
		flush_buffer_str();
	}
	return (0);
}
