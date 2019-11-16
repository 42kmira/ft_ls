/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:39:35 by kmira             #+#    #+#             */
/*   Updated: 2019/11/16 01:13:11 by kmira            ###   ########.fr       */
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
	SOCK_FILE   = 0b000000001,
	SYM_LINK    = 0b000000010,
	REG_FILE    = 0b000000100,
	BLOCK_FILE  = 0b000001000,
	DIRECTORY   = 0b000010000,
	CHAR_FILE   = 0b000100000,
	FIFO_FILE   = 0b001000000,
	BAD_FILE    = 0b010000000,
	HIDDEN_FILE = 0b100000000
}					t_inode_type;

typedef enum		e_flag_mask
{
	l_FLAG   = 0b00000000001,
	R_FLAG   = 0b00000000010,
	a_FLAG   = 0b00000000100,
	r_FLAG   = 0b00000001000,
	t_FLAG   = 0b00000010000,
	c_FLAG   = 0b00000100000,
	u_FLAG   = 0b00001000000,
	U_FLAG   = 0b00010000000,
	S_FLAG   = 0b00100000000,
	one_FLAG = 0b01000000000,
	BAD_FLAG = 0b10000000000
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
	char				file_name[FILENAME_MAX];
	size_t				file_loc;

	struct stat			stat_info;
	t_inode_type		type;
	char				*color;

	struct s_ls_inode	*left;
	struct s_ls_inode	*right;
	struct s_ls_inode	*next;

	char				*nlinks;
	char				*size;
	char				*pw_name;
	char				*gr_name;
	char				type_letter[1];
}					t_inode;

typedef struct		s_h_output
{
	u_int8_t		newline;
	u_int8_t		only_dir;
	u_int8_t		recurse_active;
	t_flag_mask		*flags;
	int				(*comparator)(t_inode *, t_inode *);
	int				total_block_size;
	int				longest_nlinks;
	int				longest_size;
	int				longest_pw_name;
	int				longest_gr_name;
}					t_h_output;

#endif
