/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:28:30 by kmira             #+#    #+#             */
/*   Updated: 2019/06/02 12:50:58 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_file(const char *file_name, t_flag_bit flags)
{
	if ((flags & FLAG_a) && (file_name[0] == '.'))
	{
		if (flags & FLAG_l)
			printf("-rw-r--r--  1 kmira  2018_october  1040 May 30 10:59 %s\n",
				file_name);
		else
			printf("%s\n", file_name);
	}
	else if ((file_name[0] != '.'))
	{
		if (flags & FLAG_l)
			printf("-rw-r--r--  1 kmira  2018_october  1040 May 30 10:59 %s\n",
				file_name);
		else
			printf("%s\n", file_name);
	}
}
