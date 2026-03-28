/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:10:21 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/03/28 16:16:28 by antoinebuet      ###   ########.fr       */
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
			number += temp * (pow(16, t));
			t++;
			i--;
		}
		return (number);
	}
	return (-1);
}
void free_mft(int **final_tab, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		free(final_tab[j]);
		j++;
	}
	free(final_tab);
}
int **malloc_final_tab(char **first_split)
{
	int **final_tab;
	int i;
	int number_line;

	i = 0;
	number_line = count_number(first_split);
	final_tab = malloc(number_line * sizeof(int *));
	if (!final_tab)
		return (0); 
	while (i < number_line)
	{
		final_tab[i] = malloc(2 * sizeof(int));
		if (!final_tab[i])
			return (free_mft(final_tab, i), NULL); //free final_tab
		i++;
 	}
	return (final_tab);
}

void free_final_tab(int **final_tab, char **first_split)
{
	int number_line;
	int i;

	number_line = count_number(first_split);
	i = 0;
	while(i < number_line)
	{
		free(final_tab[i]);
		i++;
	}
	free(final_tab);
}
int make_color(char **seconde_split)
{
	if (!seconde_split[1])
		return (put_hex("0xFFFFFF"));
	return (put_hex(seconde_split[1]));
}

static void	free_tab22(char **array)
{
	int i;

	i = 0;
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
		return (NULL);
	while (first_split[i])
	{
		seconde_split = ft_split(first_split[i], ',');
		if (!seconde_split)
			return (free_final_tab(final_tab, first_split), NULL) ; // final_tab*
		final_tab[i][0] = ft_atoi(seconde_split[0]);
		if (final_tab[i][0] > 2147483647 || final_tab[i][0] < -2147483648)
			return (free_final_tab(final_tab, first_split), free_tab22(seconde_split), NULL); // free seconde split, final_tab*
		final_tab[i][1] = make_color(seconde_split);
		if (final_tab[i][1] == -1)
			return (free_final_tab(final_tab, first_split), free_tab22(seconde_split), NULL); //free seconde split, final_tab*
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
	final_tab = malloc((size + 1) * sizeof(int **));
	while (list != NULL)
	{
		first_split = ft_split(list->value, ' ');
		if (!first_split)
			return (free(final_tab), NULL); //final_tab*
		delete_first(&list);
		final_tab[i] = seconde_split(first_split);
		if (!final_tab[i])
			return (free(final_tab), free_tab22(first_split), NULL); //final_tab premier tableau first_split*
		i++;
		free_tab22(first_split);
	}
	return (final_tab);
}
void free_list(t_node **list)
{
	while (*list)
		delete_first(list);
}

int ***open_files(int fd)
{
	t_node *list;
	int size;
	char *line;
	int ***tab_parse;

	list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		add_back(&list, ft_strtrim(line, "\n"));
		free(line);
		line = get_next_line(fd);
	}
	size = lenght_list(list);
	tab_parse = first_split(list, size);
	if (!tab_parse)
		return (free_list(&list), NULL); //free list chainé*
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
