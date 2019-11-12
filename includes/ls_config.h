/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_config.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:39:02 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 23:20:16 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CONFIG_H
# define LS_CONFIG_H

# include "ls_structs.h"
# include "color.h"

static t_ls_flag	g_flags[] =
{
	{'l', l_FLAG},
	{'R', R_FLAG},
	{'a', a_FLAG},
	{'r', r_FLAG},
	{'t', t_FLAG},
	{'1', one_FLAG},
	{'c', c_FLAG},
	{'\0', BAD_FLAG}
};

typedef struct	s_type_data
{
	t_inode_type	type;
	char			*color;
	char			letter;
}				t_type_data;

static t_type_data	g_type_table[] =
{
	{S_IFREG, BOLDLIGHT_PURPLE, 'l'},
	{S_IFREG, BOLDGREEN, 'l'},
}

#endif
