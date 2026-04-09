/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:29:37 by abuet             #+#    #+#             */
/*   Updated: 2026/04/09 13:30:17 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
