/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_config.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:39:02 by kmira             #+#    #+#             */
/*   Updated: 2019/11/16 01:12:43 by kmira            ###   ########.fr       */
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
	{'u', u_FLAG},
	{'U', U_FLAG},
	{'S', S_FLAG},
	{'\0', BAD_FLAG}
};

typedef struct	s_type_data
{
	int				key;
	t_inode_type	type;
	char			*color;
	char			letter;
}				t_type_data;

static t_type_data	g_type_table[] =
{
	{S_IFSOCK, SOCK_FILE, YELLOW, 's'},
	{S_IFLNK, SYM_LINK, BOLDGREEN, 'l'},
	{S_IFREG, REG_FILE, BOLDLIGHT_PURPLE, '-'},
	{S_IFBLK, BLOCK_FILE, BLUE, 'b'},
	{S_IFDIR, DIRECTORY, BOLDPURPLE, 'd'},
	{S_IFCHR, CHAR_FILE, BOLDBLUE, 'c'},
	{S_IFIFO, FIFO_FILE, ORANGE, 'p'},
	{0, REG_FILE, "", '-'}
};

typedef struct	s_cmp_pair
{
	t_flag_mask		key;
	int				(*comparator)(t_inode *, t_inode *);
}				t_cmp_pair;

int			ls_mtime_cmp(t_inode *a, t_inode *b);
int			ls_atime_cmp(t_inode *a, t_inode *b);
int			ls_ascii_cmp(t_inode *a, t_inode *b);
int			ls_size_cmp(t_inode *a, t_inode *b);

static t_cmp_pair	g_cmp_dispatch[] =
{
	{t_FLAG, ls_mtime_cmp},
	{u_FLAG, ls_atime_cmp},
	{S_FLAG, ls_size_cmp},
	{0, ls_ascii_cmp}
};

#endif
