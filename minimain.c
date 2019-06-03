/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 19:22:50 by kmira             #+#    #+#             */
/*   Updated: 2019/06/01 17:36:00 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>




int main(int argc, char const *argv[])
{
	DIR		*directory;
	directory = opendir(".vscode/ipch");

	if (directory != NULL)
		printf("Able to open the directory\n");

	struct dirent	*file;
	file = readdir(directory);
	file = readdir(directory);
	file = readdir(directory);
	printf("%s\n", file->d_name);


	struct stat		*info;
	info = malloc(sizeof(*info));
	stat(".vscode/ipch", info);
	if (S_ISDIR(info->st_mode))
		printf("This is indeed a directory\n");
}
