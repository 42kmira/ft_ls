/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_compare_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 22:50:24 by kmira             #+#    #+#             */
/*   Updated: 2019/06/03 02:24:44 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		compare_function_ascii
	(t_flag_bit flags, char const *file_a, char const *file_b, char const *directory_path)
{
	(void)directory_path;
	if (flags & FLAG_r)
		return (-1 * ft_strcmp(file_a, file_b));
	else
		return (ft_strcmp(file_a, file_b));
}

int		compare_function_time
	(t_flag_bit flags, char const *file_a, char const *file_b, char const *directory_path)
{
	char		path_a[MAXNAMLEN];
	char		path_b[MAXNAMLEN];
	struct stat info_a;
	struct stat info_b;

	ft_bzero(path_a, sizeof(path_a));
	concat_file_to_directory(path_a, file_a, directory_path);
	ft_bzero(&info_a, sizeof(info_a));
	stat(path_a, &info_a);
	ft_bzero(path_b, sizeof(path_b));
	concat_file_to_directory(path_b, file_b, directory_path);
	ft_bzero(&info_b, sizeof(info_b));
	stat(path_b, &info_b);
	if (info_a.st_mtime - info_b.st_mtime == 0)
		return (-1 * compare_function_ascii(flags, file_a, file_b, directory_path));
	if (flags & FLAG_r)
		return (info_a.st_mtime - info_b.st_mtime);
	else
		return (info_b.st_mtime - info_a.st_mtime);
}

void	*set_compare_function(t_flag_bit flags)
{
	int (*compare_funct)(t_flag_bit, char const *, char const *, char const *);

	if (flags & FLAG_t)
		compare_funct = &compare_function_time;
	else
		compare_funct = &compare_function_ascii;
	(void)flags;
	return (compare_funct);
}
