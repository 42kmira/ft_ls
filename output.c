/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:28:30 by kmira             #+#    #+#             */
/*   Updated: 2019/06/03 03:43:29 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_l(const char *file_name, char const *directory_path)
{
	char		path[MAXNAMLEN];
	struct stat	info;

	ft_bzero(path, sizeof(path));
	concat_file_to_directory(path, file_name, directory_path);
	ft_bzero(&info, sizeof(info));
	// printf("PATH: %s\n", path);
	stat(path, &info);
	// printf("%s%s has: %hu\n", directory_path, file_name, (uint16_t)info.st_mode);
	uint16_t mode = info.st_mode;

	static const char *rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
	static char bits[11];

	bits[0] = '-';
	strcpy(&bits[1], rwx[(mode >> 6)& 7]);
	strcpy(&bits[4], rwx[(mode >> 3)& 7]);
	strcpy(&bits[7], rwx[(mode & 7)]);
	bits[10] = '\0';

	struct group *grp;
	grp = getgrgid(info.st_gid);
	struct passwd *pw;
	pw = getpwuid(info.st_uid);
	char *groupy = grp->gr_name;
	char *owner = pw->pw_name;
	printf("%s %d %s %s %s\n", bits, info.st_nlink, owner, groupy, file_name);
}

void	print_file(const char *file_name, t_flag_bit flags, char const *directory_path)
{
	if ((flags & FLAG_a) && (file_name[0] == '.'))
	{
		if (flags & FLAG_l)
			print_l(file_name, directory_path);
		else
			printf("%s\n", file_name);
	}
	else if ((file_name[0] != '.'))
	{
		if (flags & FLAG_l)
			print_l(file_name, directory_path);
		else
			printf("%s\n", file_name);
	}
}
