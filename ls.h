/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 22:36:31 by kmira             #+#    #+#             */
/*   Updated: 2019/06/02 17:15:14 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

/*
** Used for Debugging/Development Process
*/

# include "debug.h"

# define ERROR(NAME) error_ ## NAME

# ifndef EXIT
#  define EXIT(error_msg) ft_puterror(error_msg)
# endif

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
*/

# define RELATIVE_PATH "."

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** HEADER FILES
*/

# include "ft_macro.h"
# include "ft_color.h"
# include "libft/libft.h"
# include "ls_structs.h"

# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: ls_entry.c
** Entry for the ls program
*/

void		ft_ls_main(t_flag_bit flags, char const *argv[], size_t arg_start);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: ls_recursion.c
** The real ls calls are here
*/

void		ls_recurse_into(char const *argv, t_flag_bit *flags);
void		ls_main(const char *file, t_flag_bit *flags);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: file_expansion.c
** Function dealing with opening the directory and sorting using a binary tree
*/

void		tree_traversal(t_file_tree *root, t_flag_bit flags);
void		tree_recursion(t_file_tree *root, t_flag_bit *flags);
t_file_tree	*create_tree(const char *directory, t_flag_bit flags);
void		insert_to_tree_structure
			(t_file_tree *root, struct dirent *file, char const *dir_path);
void		free_tree(t_file_tree *root);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: flag_parser.c
** Deals with getting the flag(s) from user input.
*/

t_flag_bit	set_flags(char const *argv[], size_t *arguement_start);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: output.c
** Deals with printing
*/

void		print_file(const char *file_name, t_flag_bit flags);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: utils.c
** Small useful functions
*/

void		concat_file_to_directory
			(char *dest, char const *file_name, char const *directory_path);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: errors.c
** Deals with functions that have to do with errors
*/

void		error_flag(t_flag_bit flag);
void		error_null_argv(void);

#endif
