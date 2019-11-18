/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:38:23 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 05:31:11 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

char			*program_name(char *arg_zero)
{
	static char *name;

	if (arg_zero != FETCH_NAME && name != NULL)
		ft_puterror("Error on program name: reassign to name.");
	if (arg_zero == FETCH_NAME && name == NULL)
		ft_puterror("Error on program name: name has not been assigned yet");
	if (name == NULL)
	{
		if (arg_zero[0] == '.' && arg_zero[1] == '/')
			name = &arg_zero[2];
		else
			name = arg_zero;
	}
	return (name);
}

void			fetch_cmp_function(t_h_output *h_output)
{
	int			i;
	t_flag_mask *key;

	i = 0;
	key = h_output->flags;
	h_output->comparator = ls_ascii_cmp;
	while (g_cmp_dispatch[i].key != 0)
	{
		if (*key & g_cmp_dispatch[i].key)
			h_output->comparator = g_cmp_dispatch[i].comparator;
		i++;
	}
}

void			padd_string(int pad_length)
{
	int		i;
	char	*result;

	i = 0;
	if (pad_length <= 0)
		return ;
	result = malloc(sizeof(pad_length) + 1);
	result[pad_length] = '\0';
	while (i < pad_length)
	{
		result[i] = ' ';
		i = i + 1;
	}
	buffer_output_str(result, 0);
}

struct timespec	*fetch_time(struct stat *stat_info, t_flag_mask *flags)
{
	if (*flags & u_FLAG)
		return (&stat_info->st_atimespec);
	else if (*flags & U_FLAG)
		return (&stat_info->st_birthtimespec);
	else
		return (&stat_info->st_mtimespec);
}
