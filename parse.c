/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:10:21 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/03/23 15:46:37 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int verif_name(char *file_name)
{
	int i;

	i = 0;
	while (file_name[i])
	{
		i++;
	}
	if (file_name[i - 4] == '.' && file_name[i - 3] == 'f' && 
		file_name[i - 2] == 'd' && file_name[i - 1] == 'f')
		return (1);
	return (0);
}

int count_number(char **first_split)
{
	int i;

	i = 0;
	while(first_split[i])
		i++;
	return (i);
}
int put_int(char ascii)
{
	if (ascii >= '0' && ascii <= '9')
		return (ascii - 48);
	else if (ascii >= 'a' && ascii <= 'z')
		return (ascii - 97 + 10); 
	else if (ascii >= 'A' && ascii <= 'Z')
		return (ascii - 65 + 10);
	return (-1);
}
int put_hex(char *hexa)
{
	int i;
	int number;
	int t;
	int temp;

	i = 0;
	number = 0;
	t = 0;
	while (hexa[i])
		i++;
	if(hexa[0] == '0' && hexa[1] == 'x' && i == 8)
	{
		i--;
		while (i > 2)
		{
			temp = put_int(hexa[i]);
			if (temp == -1)
				return (-1);
			number += temp * (power(16, t));
			t++;
			i--;
		}
		return (number);
	}
	return (-1);
}
int **malloc_final_tab(char **first_split)
{
	int **final_tab;
	int i;
	int number_line;

	i = 0;
	number_line = count_number(first_split);
	final_tab = malloc(number_line * sizeof(int));
	if (!final_tab)
		return (0); 
	while (i < number_line)
	{
		final_tab[i] = malloc(2 * sizeof(char));
		if (!final_tab)
			return ; //free final_tab
 	}
	return (final_tab);
}
int make_color(char **seconde_split)
{
	if (!seconde_split[1])
		return (put_hex('0xFFFFFF'));
	return (put_hex(seconde_split[1]));
}

static void	free_tab22(char **array)
{
	int i;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
int **seconde_split(char **first_split)
{
	char **seconde_split;
	int **final_tab;
	int i;

	i = 0;
	final_tab = malloc_final_tab(first_split);
	if (!final_tab)
		return (free_array22(first_split), 0); //faut free first_split*
	while (first_split[i])
	{
		seconde_split = split(first_split[i], ',');
		if (!seconde_split)
			return (free_tab22(first_split), 0) ; // firstsplit*
		final_tab[i][0] = ft_atoi(seconde_split[0]);
		if (final_tab[i][0] == 2147483648)
			return (free_tab22(first_split), free_tab22(seconde_split), 0); // free seconde split, fist_split*
		final_tab[i][1] = make_color(seconde_split);
		if (final_tab[i][1] == -1)
			return (free_tab22(first_split), free_tab22(seconde_split), 0); //free seconde split, first_split,*
		i++;
		free_tab22(seconde_split); //seconde split*
	}
	return (final_tab);
}
int ***first_split(t_node *list, int size)
{
	char **first_split;
	int ***final_tab;
	int i;

	i = 0;
	final_tab = malloc((size + 1) * sizeof(int));
	while (list != NULL)
	{
		first_split = split(list->value, ' ');
		if (!first_split)
			return (0); //final_tab
		delete_first(&list);
		final_tab[i] = seconde_split(first_split);
		if (!final_tab)
			return (free_tab22(first_split), 0); //final_tab, first_split
		i++;
		free_tab22(first_split);
	}
	return (final_tab);
}

int ***open_files(int fd)
{
	t_node *list;
	int size;
	char *line;
	char ***tab_parse;

	list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		add_back(&list, line);
		free(line);
	}
	size = lenght_list(list);
	tab_parse = first_split(list, size);
	if (!tab_parse)
		return ; //free list chainé
	return (tab_parse);
}

int ***parse_map(char *file_name)
{
	int fd;
	int ***tab_parse;

	if (verif_name(file_name) != 1)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tab_parse = open_files(fd);
	if (!tab_parse)
		return (NULL);
	return (tab_parse);
}
