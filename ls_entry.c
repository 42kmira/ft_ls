/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_entry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 02:51:43 by kmira             #+#    #+#             */
/*   Updated: 2019/06/03 02:50:00 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_ls_main(t_flag_bit flags, char const *argv[], size_t arguement_start)
{
	size_t		i;
	struct stat	info;
	int			newline_needed;

	if (argv == NULL)
		ERROR(null_argv)();
	else if (argv[arguement_start] == NULL)
		ls_recurse_into(RELATIVE_PATH, &flags);
	else if (argv[arguement_start + 1] == NULL)
	{
		stat(argv[arguement_start], &info);
		if (S_ISDIR(info.st_mode))
			ls_recurse_into(argv[arguement_start], &flags);
		else
			print_file(argv[arguement_start], flags | FLAG_a, "");
	}
	else
	{
		//sort things
		i = arguement_start;

		newline_needed = 0;
		while (argv[i])
		{
			ft_bzero(&info, sizeof(info));
			stat(argv[i], &info);
			if (!(S_ISDIR(info.st_mode)))
			{
				newline_needed = 1;
				printf("%s\n", argv[i]);
			}
			i++;
		}
		if (newline_needed)
			flags = flags ^ FLAG_FIRST_CALL;
		i = arguement_start;
		while (argv[i])
		{
			ft_bzero(&info, sizeof(info));
			stat(argv[i], &info);
			if (S_ISDIR(info.st_mode))
				ls_main(argv[i], &flags);
			i++;
		}
	}
}
