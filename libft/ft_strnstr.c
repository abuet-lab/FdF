/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:35:37 by abuet             #+#    #+#             */
/*   Updated: 2025/10/28 13:43:08 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	t;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *) big);
	while (big[i] && i + ft_strlen(little) <= len)
	{
		t = 0;
		while (big[i + t] == little[t] && ft_strlen(little) > t)
			t++;
		if (ft_strlen(little) == t)
			return ((char *) big + i);
		i++;
	}
	return (NULL);
}
