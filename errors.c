/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 02:33:40 by kmira             #+#    #+#             */
/*   Updated: 2019/05/30 03:13:23 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	error_flag(t_flag_bit flag)
{
	flag = -flag;
	write(1, RED"ft_ls illegal option -- ", 30);
	write(1, &flag, 1);
	EXIT("\nusage: ft_ls [-1Rart]"COLOR_RESET);
}

void	error_null_argv(void)
{
	write(1, RED"ft_ls: argv points to NULL\nCannot access"COLOR_RESET, 50);
}
