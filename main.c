/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:18:08 by kmira             #+#    #+#             */
/*   Updated: 2019/05/31 15:55:16 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		main(int ac, char const *argv[])
{
	t_flag_bit	flags;
	size_t		arguement_start;

	flags = set_flags(argv, &arguement_start);
	flags |= FLAG_FIRST_CALL;
	if (flags < 0)
		ERROR(flag)(flags);
	ft_ls_main(flags, argv, arguement_start);
	(void)ac;
	return (0);
}
