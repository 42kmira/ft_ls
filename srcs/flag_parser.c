/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:04:24 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 16:47:11 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

static void	toggle_flag(char key, t_flag_mask *dest)
{
	size_t	i;

	i = 0;
	while (g_flags[i].flag_mask != BAD_FLAG)
	{
		if (key == g_flags[i].key)
		{
			*dest |= g_flags[i].flag_mask;
			break ;
		}
		i++;
	}
	if (g_flags[i].key == '\0')
	{
		*dest |= BAD_FLAG;
		error_bad_flag(key);
	}
}

static void	clean_up_flags(t_flag_mask *flags, char key)
{
	if (*flags & l_FLAG && *flags & one_FLAG)
	{
		if (key == '1')
			*flags &= ~(l_FLAG);
		else
			*flags &= ~(one_FLAG);
	}
	if ((*flags & u_FLAG || *flags & U_FLAG) && *flags & c_FLAG)
	{
		if (key == 'c')
			*flags &= ~(u_FLAG | U_FLAG);
		else
			*flags &= ~(c_FLAG);
	}
	if (*flags & f_FLAG)
		*flags |= a_FLAG;
}

t_flag_mask	fetch_flags(size_t *at, char **args)
{
	size_t		j;
	char		key;
	t_flag_mask	result;

	result = 0;
	while (args[*at] != NULL && args[*at][0] == '-' && !(result & BAD_FLAG))
	{
		if (args[*at][1] == '-' && args[*at][2] == '\0')
			break ;
		j = 1;
		while (args[*at][j] != '\0' && !(result & BAD_FLAG))
		{
			key = args[*at][j];
			toggle_flag(key, &result);
			clean_up_flags(&result, key);
			j++;
		}
		*at = *at + 1;
	}
	return (result);
}
