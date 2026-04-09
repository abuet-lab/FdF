/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:30:59 by abuet             #+#    #+#             */
/*   Updated: 2026/04/09 14:44:16 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	verif_name(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 4] == '.' && file_name[i - 3] == 'f'
		&& file_name[i - 2] == 'd' && file_name[i - 1] == 'f')
		return (1);
	return (0);
}

int	count_number(char **first_split)
{
	int	i;

	i = 0;
	while (first_split[i])
		i++;
	return (i);
}

static int	put_int(char ascii)
{
	if (ascii >= '0' && ascii <= '9')
		return (ascii - 48);
	else if (ascii >= 'a' && ascii <= 'z')
		return (ascii - 97 + 10);
	else if (ascii >= 'A' && ascii <= 'Z')
		return (ascii - 65 + 10);
	return (-1);
}

int	put_hex(char *hexa)
{
	int	i;
	int	number;
	int	temp;

	if (!hexa || hexa[0] != '0' || hexa[1] != 'x')
		return (-1);
	i = 2;
	number = 0;
	while (hexa[i])
	{
		temp = put_int(hexa[i]);
		if (temp == -1)
			return (-1);
		number = number * 16 + temp;
		i++;
	}
	return (number);
}

int	verif_line(char **first_split, t_firstsplit *t)
{
	int	i;

	i = 0;
	if (t->line == -1)
	{
		while (first_split[i])
			i++;
		t->line = i;
		return (i);
	}
	while (first_split[i])
		i++;
	if (i != t->line)
		return (0);
	return (1);
}
