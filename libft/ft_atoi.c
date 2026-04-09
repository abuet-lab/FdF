/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:58:57 by abuet             #+#    #+#             */
/*   Updated: 2026/03/28 21:20:40 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int		i;
	char	neg;
	int		result;

	i = 0;
	neg = 1;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i]
		== '\n' || nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
		neg *= -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result += (nptr[i] - 48);
		if (nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
			result *= 10;
		i++;
	}
	return (result * neg);
}
