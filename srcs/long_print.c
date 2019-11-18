/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:35:12 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 00:00:32 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

#define SIX_MONTHS (15778463)

static void	print_permissions(mode_t permission)
{
	char	buff[10];

	ft_memset(buff, '-', sizeof(buff));
	buff[9] = '\0';
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
	buffer_output_str(buff, 0);
}

static void	print_links(char *nlinks, int longest)
{
	int	padd;

	padd = longest - ft_strlen(nlinks);
	padd_string(padd);
	buffer_output_str(nlinks, 0);
}

static void	print_pw_and_gr_name(char *pw_name, char *gr_name, t_h_output *h_output)
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


static void	print_size(char *size, int longest, struct stat stat_info)
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

static void	print_time(struct stat *stat_info, t_h_output *h_output)
{
	char			time_string[26];
	struct timespec	*time_stamp;

	time_string[0] = ' ';
	time_stamp = fetch_time(stat_info, h_output->flags);
	ft_strncpy(&time_string[1], ctime(&time_stamp->tv_sec) + 4, 7);
	if (time_stamp->tv_sec < time(0) - SIX_MONTHS ||
		time_stamp->tv_sec > time(0) + SIX_MONTHS)
		ft_strncpy(time_string + 8, ctime(&time_stamp->tv_sec) + 19, 5);
	else
		ft_strncpy(time_string + 8, ctime(&time_stamp->tv_sec) + 11, 5);
	time_string[13] = '\0';
	buffer_output_str(time_string, 0);
}

void	long_print(t_h_output *h_output, t_inode *root)
{
	char			*real_path;

	if (*h_output->flags & c_FLAG)
		buffer_output_str(root->color, 0);
	buffer_output_str(root->type_letter, 0);
	print_permissions(root->stat_info.st_mode);
	print_links(root->nlinks, h_output->longest_nlinks + 2);
	print_pw_and_gr_name(root->pw_name, root->gr_name, h_output);
	print_size(root->size, h_output->longest_size + 2, root->stat_info);
	print_time(&root->stat_info, h_output);
	buffer_output_str(" ", 0);
	buffer_output_str(&root->file_name[root->file_loc], 0);
	if (root->type & SYM_LINK)
	{
		buffer_output_str(" -> ", 0);
		real_path = ft_strnew(30);
		readlink(root->file_name, real_path, 30);
		buffer_output_str(real_path, 0);
	}
	if (*h_output->flags & c_FLAG)
		buffer_output_str(COLOR_RESET, 0);
	buffer_output_str("\n", 0);
}
