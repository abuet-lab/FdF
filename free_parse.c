/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:33:19 by abuet             #+#    #+#             */
/*   Updated: 2026/04/09 13:38:48 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_final_tab(long int **final_tab)
{
	if (!final_tab)
		return ;
	free(final_tab[0]);
	free(final_tab);
}

void	free_tab22(char **array)
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

void	free_list(t_node **list)
{
	while (*list)
		delete_first(list);
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
		return (free(final_tab), NULL);
	while (i < number_line)
	{
		final_tab[i] = &temp[i * 2];
		i++;
	}
	return (final_tab);
}