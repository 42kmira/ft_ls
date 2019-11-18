/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:38:23 by kmira             #+#    #+#             */
/*   Updated: 2019/11/18 06:21:30 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_main.h"

char			*program_name(char *arg_zero)
{
	static char *name;

	if (arg_zero != FETCH_NAME && name != NULL)
		ft_puterror("Error on program name: reassign to name.");
	if (arg_zero == FETCH_NAME && name == NULL)
		ft_puterror("Error on program name: name has not been assigned yet");
	if (name == NULL)
	{
		if (arg_zero[0] == '.' && arg_zero[1] == '/')
			name = &arg_zero[2];
		else
			name = arg_zero;
	}
	return (name);
}

void			fetch_cmp_function(t_h_output *h_output)
{
	int			i;
	t_flag_mask *key;

	i = 0;
	key = h_output->flags;
	h_output->comparator = ls_ascii_cmp;
	while (g_cmp_dispatch[i].key != 0)
	{
		if (*key & g_cmp_dispatch[i].key)
			h_output->comparator = g_cmp_dispatch[i].comparator;
		i++;
	}
}

void			padd_string(int pad_length)
{
	int		i;
	char	*result;

	i = 0;
	if (pad_length <= 0)
		return ;
	result = malloc(sizeof(pad_length) + 1);
	result[pad_length] = '\0';
	while (i < pad_length)
	{
		result[i] = ' ';
		i = i + 1;
	}
	buffer_output_str(result, 0);
}

char			get_xattribute(char *file_name)
{
	ssize_t	xattr;
	acl_t	acl;
	char	special;

	xattr = listxattr(file_name, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_link_np(file_name, ACL_TYPE_EXTENDED);
	if (xattr > 0)
		special = '@';
	else if (acl != NULL)
		special = '+';
	else
		special = ' ';
	return (special);
}
