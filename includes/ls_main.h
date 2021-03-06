/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:34:37 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 16:46:50 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_MAIN_H
# define LS_MAIN_H

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** HEADERS
*/

# include "color.h"
# include "libft.h"
# include "ls_config.h"
# include "ls_structs.h"

# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <time.h>

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: flag_parser.c
** Description: Handles flag functionality
*/

t_flag_mask	fetch_flags(size_t *at, char **args);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: get_inodes.c, create_inodes.c
** Description: Creates inodes.
*/

void		add_inode(t_inode **head, char *file_name,
				char *dir_name, t_h_output *h_output);
t_inode		*expand_from_path(char *file_name, char *dir_name);
void		insert_inode(t_inode *root, t_inode *node, t_h_output *h_output);

t_inode		*extract_directories(t_inode *root);
void		extract_algo(t_inode *root, t_inode **starting);
t_inode		*get_inodes_from_args(char **args, t_h_output *h_output);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: list_directory.c
** Description: Deals with going from inodes to directories.
*/

void		handle_directory(t_inode *root,
			t_h_output *h_output, t_flag_mask *flags);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: comp_functions.c
** Description: Functions about comparing.
*/

int			ls_master_cmp(t_inode *a, t_inode *b, t_h_output *h_output);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: ls_utils.c
** Description: utility functions
*/

# define FETCH_NAME (char *)1

char		*program_name(char *arg_zero);
void		fetch_cmp_function(t_h_output *h_output);
void		padd_string(int pad_length);
void		free_tree(t_inode *root);
char		get_xattribute(char *file_name);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: output_utils.c
** Description: Does debugging stuff.
*/

void		init_h_output(t_h_output *h_output, t_flag_mask *flags);
void		find_longest_out_data(t_inode *root, t_h_output *h_output);
void		zero_out_length_data(t_h_output *h_output);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: buffer.c
** Description: functions about the buffer.
*/

void		buffer_output_str(char *str, int final);
void		flush_buffer_str(void);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: io_out.c
** Description: Handles the outputting of the message
*/

void		print_tree(t_inode *root, t_h_output *h_output, t_inode_type mask);
void		print_directory_header(t_inode *directory, t_h_output *h_output);
void		short_print(t_h_output *h_output, t_inode *root);
void		long_print(t_h_output *h_output, t_inode *root);
void		print_total_blocks(int total);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: long_print.c
** Description: Handles the printing for the -l flag
*/

void		print_permissions(mode_t permission, char *file_name);
void		print_links(char *nlinks, int longest);
void		print_pw_gr_names(char *pw_name, char *gr_name, t_h_output *h_out);
void		print_size(char *size, int longest, struct stat stat_info);
void		print_time(struct stat *stat_info, t_h_output *h_output);

/*
** -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-  -_---_-_-
** FILE: ls_error.c
** Description: Deals with errors.
*/

void		error_ls_usage(void);
void		error_stat(t_inode *file);
void		error_bad_flag(char bad_key);
void		error_cannot_open_file(char *file_name);

#endif
