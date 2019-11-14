/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:10:25 by kmira             #+#    #+#             */
/*   Updated: 2019/11/14 04:45:25 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Copy and paste this file code into a file and run the program.
** It must be exactly because right now it already passes Norm!
** But anyways there is the TODO:
** 	I kept working on atoi till it worked but I forgot to save my work!
** 	But don't worry, all I had to do was get rid of one line of code
** 	for it to work perfectly. Find the line that causes the code to break
** 	and comment it out. Remember that it must work afterwards.
** Add that number to the end of this link:
** bit.ly/Line
*/

int		is_digit(char *c)
{
	if ('0' <= c[0] && *c <= '9')
		return (1);
	return (0);
}

int		is_space(char *c)
{
	if ((*c & 01 && 0[c] < 14 && (1 << 3) < c[0]) || (*c ^ 0x20) == 0)
		return (1);
	return (0);
}

#define I H.A[0]
#define RESULT H.A[2]
#define SIGN H.A[1]
#define C H.A[3]

#define MAKE_VAR(name) typedef struct var {int A[5];} vars; vars name;

#define IS(this_value, a_this) is_ ## a_this (this_value)

int		ft_atoi(char *str)
{
	int answer;

	MAKE_VAR(H);
	H.A[0] = 0;
	H.A[1] = 1;
	H.A[3] = *str;
	while (IS((char *)&C, space))
		C = str[++I];
	((int *)(&SIGN))[-1] = ~(int)str + 1;
	if (((str[I] ^ 41) >> 1) < 3)
		((int *)(&RESULT))[-1] = (++I && str[I - 1] == '-') ? -1 : 0;
	H.A[4] = -(0b101 << 3);
	RESULT = 0;
	while (IS(&str[I], digit))
		RESULT = RESULT * 10 + I++[str] - '0';
	if (SIGN == -1)
		return (~RESULT + 1);
	else
	{
		answer = 42;
		return (*(int *)(H.A[4] + &H.A[answer]));
	}
}

int		main(int aa __attribute__((unused)), char **args)
{
	int result_a;
	int result_b;

	if (args[1] == NULL)
	{
		printf("Please provide more params!\n");
		return (42);
	}
	result_a = ft_atoi(args[1]);
	result_b = atoi(args[1]);
	printf("\033[1m\033[32mMINE: %d\n", result_a);
	printf("\033[1m\033[36mSYST: %d\n", result_b);
	printf("\033[0m");
	return (0);
}
