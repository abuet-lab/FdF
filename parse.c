/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:10:21 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/09 23:15:41 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	make_color(char **seconde_split)
{
	int	hexa;

	if (!seconde_split[1])
		return (put_hex("0xFFFFFF"));
	hexa = put_hex(seconde_split[1]);
	if (hexa == -1)
		return (-1);
	return (hexa);
}

long int	**seconde_split(char **first_split, t_sizetab *sizetab)
{
	char		**seconde_split;
	long int	**final_tab;
	int			i;

	i = 0;
	final_tab = malloc_final_tab(first_split, sizetab);
	if (!final_tab)
		return (NULL);
	while (first_split[i])
	{
		seconde_split = ft_split(first_split[i], ',');
		if (!seconde_split)
			return (free_final_tab(final_tab), NULL);
		final_tab[i][0] = ft_atoi(seconde_split[0]);
		if (final_tab[i][0] > 2147483647 || final_tab[i][0] < -2147483648)
			return (free_final_tab(final_tab),
				free_tab22(seconde_split), NULL);
		final_tab[i][1] = make_color(seconde_split);
		if (final_tab[i][1] == -1)
			return (free_final_tab(final_tab),
				free_tab22(seconde_split), NULL);
		i++;
		free_tab22(seconde_split);
	}
	return (final_tab);
}

long int	***first_split(t_node *list, int size, t_sizetab *sizetab)
{
	char			**first_split;
	long int		***final_tab;
	t_firstsplit	t;

	t.i = 0;
	t.line = -1;
	final_tab = malloc((size + 1) * sizeof(int **));
	if (!final_tab)
		return (NULL);
	while (list != NULL)
	{
		first_split = ft_split(list->value, ' ');
		if (!first_split)
			return (free(final_tab), NULL);
		if (verif_line(first_split, &t) == 0)
			return (free_tab33(final_tab, &t), free_tab22(first_split), NULL);
		final_tab[t.i] = seconde_split(first_split, sizetab);
		if (!final_tab[t.i])
			return (free_tab33(final_tab, &t), free_tab22(first_split), NULL);
		t.i++;
		free_tab22(first_split);
		list = list->next;
	}
	return (final_tab);
}

long int	***open_files(int fd, t_sizetab *sizetab)
{
	t_node		*list;
	int			size;
	char		*line;
	long int	***tab_parse;

	list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		add_first(&list, ft_strtrim(line, "\n"));
		free(line);
		line = get_next_line(fd);
	}
	reverse_list(&list);
	size = lenght_list(list);
	sizetab->line = size;
	if (size < 2)
		return (free_list(&list), NULL);
	tab_parse = first_split(list, size, sizetab);
	free_list(&list);
	if (!tab_parse)
		return (NULL);
	return (tab_parse);
}

long int	***parse_map(char *file_name, t_sizetab *sizetab)
{
	int			fd;
	long int	***tab_parse;

	if (verif_name(file_name) != 1)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tab_parse = open_files(fd, sizetab);
	if (!tab_parse)
		return (close(fd), NULL);
	sizetab->max_z = find_max(tab_parse, sizetab);
	sizetab->min_z = find_min(tab_parse, sizetab);
	close(fd);
	return (tab_parse);
}
