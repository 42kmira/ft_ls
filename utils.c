/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:39:02 by kmira             #+#    #+#             */
/*   Updated: 2019/06/02 22:47:10 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	concat_file_to_directory
	(char *dest, char const *file_name, char const *directory_path)
{
	ft_strcat(dest, directory_path);
	ft_strcat(dest, "/");
	ft_strcat(dest, file_name);
}
