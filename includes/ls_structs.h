/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:39:35 by kmira             #+#    #+#             */
/*   Updated: 2019/11/11 14:18:27 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_STRUCTS_H
# define LS_STRUCTS_H

# include <stddef.h>
# include <dirent.h>
# include <sys/stat.h>

typedef struct		s_string
{
	char			*ptr;
	size_t			length;
}					t_string;

typedef enum		e_inode_type
{
	BAD_FILE = 0b0001,
	DIRECTORY = 0b0010,
	REG_FILE = 0b0100,
	HIDDEN_FILE = 0b1000
}					t_inode_type;

typedef enum		e_flag_mask
{
	l_FLAG = 0b00000001,
	R_FLAG = 0b00000010,
	a_FLAG = 0b00000100,
	r_FLAG = 0b00001000,
	t_FLAG = 0b00010000,
	c_FLAG = 0b00100000,
	one_FLAG = 0b01000000,
	BAD_FLAG = 0b10000000
}					t_flag_mask;

typedef struct		s_ls_flag
{
	char			key;
	t_flag_mask		flag_mask;
}					t_ls_flag;

# define LEFT_NODE 1
# define RIGHT_NODE -1

typedef	struct		s_ls_inode
{
	t_inode_type		type;
	char				file_name[FILENAME_MAX];
	size_t				file_loc;
	char				*color;
	struct s_ls_inode	*left;
	struct s_ls_inode	*right;
	struct s_ls_inode	*next;
	struct stat			stat_info;
	char				*size;
	int					size_length;
	char				*print_debug;
}					t_inode;

typedef struct		s_h_output
{
	u_int8_t		newline;
	u_int8_t		only_dir;
	u_int8_t		recurse_active;
	t_flag_mask		*flags;
	int				(*comparator)(t_inode *, t_inode *);
	int				longest_size;
}					t_h_output;

#endif
