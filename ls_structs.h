/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 22:59:09 by kmira             #+#    #+#             */
/*   Updated: 2019/06/02 15:02:24 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_STRUCTS_H
# define LS_STRUCTS_H

# include <dirent.h>

enum	e_myerrors {
	UNKNOWN_FLAG = 1
};

# define IS_SORTING( FLAG ) ( FLAG & 0b11000 )

typedef int16_t	t_flag_bit;

enum	e_flags
{
	FLAG_FIRST_CALL =
	0b000001,

	FLAG_l =
	0b000010,

	FLAG_R =
	0b000100,

	FLAG_a =
	0b001000,

/*
** Below are sorting flags
*/

	FLAG_r =
	0b010000,

	FLAG_t =
	0b100000
};

typedef struct			s_flags
{
	char				flag;
	t_flag_bit			flag_mask;
}						t_flags;

typedef struct			s_file_tree
{
	char				d_name[FILENAME_MAX];
	char				path_name[__DARWIN_MAXPATHLEN];

	struct s_file_tree	*smaller;
	struct s_file_tree	*greater;
}						t_file_tree;

#endif
