/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:35:12 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 06:24:54 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

#define SIX_MONTHS (15778463)

void	print_permissions(mode_t permission, char *file_name)
{
	char	buff[11];

	ft_memset(buff, '-', sizeof(buff));
	buff[10] = '\0';
	if (permission & S_IRUSR)
		buff[0] = 'r';
	if (permission & S_IWUSR)
		buff[1] = 'w';
	if (permission & S_IXUSR)
		buff[2] = 'x';
	if (permission & S_IRGRP)
		buff[3] = 'r';
	if (permission & S_IWGRP)
		buff[4] = 'w';
	if (permission & S_IXGRP)
		buff[5] = 'x';
	if (permission & S_IROTH)
		buff[6] = 'r';
	if (permission & S_IWOTH)
		buff[7] = 'w';
	if (permission & S_IXOTH)
		buff[8] = 'x';
	buff[9] = get_xattribute(file_name);
	buffer_output_str(buff, 0);
}

void	print_links(char *nlinks, int longest)
{
	int	padd;

	padd = longest - ft_strlen(nlinks);
	padd_string(padd);
	buffer_output_str(nlinks, 0);
}

void	print_pw_gr_names(char *pw_name, char *gr_name, t_h_output *h_output)
{
	int padd;

	buffer_output_str(" ", 0);
	padd = h_output->longest_pw_name - ft_strlen(pw_name);
	buffer_output_str(pw_name, 0);
	padd_string(padd + 2);
	padd = h_output->longest_gr_name - ft_strlen(gr_name);
	buffer_output_str(gr_name, 0);
	padd_string(padd + 1);
}

void	print_size(char *size, int longest, struct stat stat_info)
{
	int		padd;
	char	*buff;

	if ((stat_info.st_mode & S_IFMT) == S_IFCHR
	|| (stat_info.st_mode & S_IFMT) == S_IFCHR)
	{
		buff = ft_itoa(major(stat_info.st_rdev));
		padd = 3 - ft_strlen(buff);
		padd_string(padd);
		buffer_output_str(buff, 0);
		buffer_output_str(", ", 0);
		free(buff);
		buff = ft_itoa(minor(stat_info.st_rdev));
		padd = 3 - ft_strlen(buff);
		padd_string(padd);
		buffer_output_str(buff, 0);
		free(buff);
	}
	else
	{
		padd = longest - ft_strlen(size);
		padd_string(padd);
		buffer_output_str(size, 0);
	}
}

void	print_time(struct stat *stat_info, t_h_output *h_output)
{
	char			time_string[26];
	struct timespec	*time_stamp;

	time_string[0] = ' ';
	if (*h_output->flags & u_FLAG)
		time_stamp = &stat_info->st_atimespec;
	else if (*h_output->flags & U_FLAG)
		time_stamp = &stat_info->st_birthtimespec;
	else
		time_stamp = &stat_info->st_mtimespec;
	ft_strncpy(&time_string[1], ctime(&time_stamp->tv_sec) + 4, 7);
	if (time_stamp->tv_sec < time(0) - SIX_MONTHS ||
		time_stamp->tv_sec > time(0) + SIX_MONTHS)
		ft_strncpy(time_string + 8, ctime(&time_stamp->tv_sec) + 19, 5);
	else
		ft_strncpy(time_string + 8, ctime(&time_stamp->tv_sec) + 11, 5);
	time_string[13] = '\0';
	buffer_output_str(time_string, 0);
}
