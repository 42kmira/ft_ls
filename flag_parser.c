/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 23:50:28 by kmira             #+#    #+#             */
/*   Updated: 2019/05/30 10:35:20 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

#define FLAG(NAME) { char_ ## NAME, FLAG_ ## NAME}
#define UNDEFINED_FLAG '\0'

t_flags				g_flags[] =
{
	FLAG(l),
	FLAG(R),
	FLAG(a),
	FLAG(R),
	FLAG(t),
	{UNDEFINED_FLAG, 0}
};

static t_flag_bit	toggle_bits_of(t_flag_bit flags, unsigned char const c)
{
	size_t		i;

	i = 0;
	while (g_flags[i].flag != UNDEFINED_FLAG && g_flags[i].flag != c)
		i++;
	if (g_flags[i].flag == UNDEFINED_FLAG)
		return (-c);
	flags = flags | g_flags[i].flag_mask;
	return (flags);
}

t_flag_bit			set_flags(char const *argv[], size_t *arguement_start)
{
	size_t		i;
	size_t		j;
	t_flag_bit	flags;

	flags = 0;
	i = 1;
	while (argv[i] != NULL && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			flags = toggle_bits_of(flags, (unsigned char)argv[i][j]);
			if (flags < 0)
				return (flags);
			j++;
		}
		i++;
	}
	*arguement_start = i;
	return (flags);
}
