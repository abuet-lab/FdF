/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:10:21 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/09 10:29:33 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	verif_name(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 4] == '.' && file_name[i - 3] == 'f' && 
		file_name[i - 2] == 'd' && file_name[i - 1] == 'f')
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
int	put_int(char ascii)
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

long int	**malloc_final_tab(char **first_split, t_sizetab *sizetab)
{
	long int	**final_tab;
	long int	*temp;
	int			i;
	int			number_line;

	i = 0;
	number_line = count_number(first_split);
	sizetab->colone = number_line;
	final_tab = malloc(number_line * sizeof(long int *));
	if (!final_tab)
		return (0);
	temp = malloc(2 * number_line * sizeof(long int));
	if (!temp)
		return (free(final_tab), NULL);//free final_tab
	while (i < number_line)
	{
		final_tab[i] = &temp[i * 2];
		i++;
	}	
	return (final_tab);
}

void	free_final_tab(long int **final_tab)
{
	if (!final_tab)
		return ;
	free(final_tab[0]);
	free(final_tab);
}
int	make_color(char **seconde_split)
{
	int	hexa;

	if (!seconde_split[1])
		return (put_hex("0xFFFFFF"));
	hexa = put_hex(seconde_split[1]);
	if (hexa == -1)
		return (-1);
	return (hexa); //attention j'ai pascheck de put exa
}

static void	free_tab22(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
			return (free_final_tab(final_tab), NULL); // final_tab*
		final_tab[i][0] = ft_atoi(seconde_split[0]);
		if (final_tab[i][0] > 2147483647 || final_tab[i][0] < -2147483648)
			return (free_final_tab(final_tab),
				free_tab22(seconde_split), NULL); // free seconde split, final_tab*
		final_tab[i][1] = make_color(seconde_split);
		if (final_tab[i][1] == -1)
			return (free_final_tab(final_tab),
				free_tab22(seconde_split), NULL); //free seconde split, final_tab*
		i++;
		free_tab22(seconde_split); //seconde split*
	}
	return (final_tab);
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
void	free_tab33(long int ***final_tab, t_firstsplit *t)
{
	int	j;

	j = 0;
	while (j < (t->i))
	{
		free(final_tab[j][0]);
		free(final_tab[j]);
		j++;
	}
	free(final_tab);
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
			return (free(final_tab), NULL); //final_tab*
		if (verif_line(first_split, &t) == 0) //marche pas
			return (free_tab33(final_tab, &t), free_tab22(first_split), NULL);
		final_tab[t.i] = seconde_split(first_split, sizetab);
		if (!final_tab[t.i])
			return (free_tab33(final_tab, &t), free_tab22(first_split), NULL); //final_tab premier tableau first_split*
		t.i++;
		free_tab22(first_split);
		list = list->next;
	}
	return (final_tab);
}
void	free_list(t_node **list)
{
	while (*list)
		delete_first(list);
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
		return (free_list(&list), NULL); //free list chainé*
	tab_parse = first_split(list, size, sizetab);
	free_list(&list);
	if (!tab_parse)
		return (NULL); //free list chainé*
	return (tab_parse);
}

int	find_max(long ***tab_parse, t_sizetab *sizetab)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = tab_parse[0][0][0];
	while (i < sizetab->line)
	{
		j = 0;
		while (j < sizetab->colone)
		{
			if (max < tab_parse[i][j][0])
				max = tab_parse[i][j][0];
			j++;
		}
		i++;
	}
	return (max);
}

int	find_min(long ***tab_parse, t_sizetab *sizetab)
{
	int	i;
	int	j;
	int	min;

	i = 0;
	min = tab_parse[0][0][0];
	while (i < sizetab->line)
	{
		j = 0;
		while (j < sizetab->colone)
		{
			if (min > tab_parse[i][j][0])
				min = tab_parse[i][j][0];
			j++;
		}
		i++;
	}
	return (min);
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
		return (NULL);
	sizetab->max_z = find_max(tab_parse, sizetab);
	sizetab->min_z = find_min(tab_parse, sizetab);
	return (tab_parse);
}
