/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:01:22 by abuet             #+#    #+#             */
/*   Updated: 2025/10/28 13:43:11 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	const char	*temp;

	temp = (char *) s;
	i = ft_strlen(temp);
	while (i > 0)
	{
		if (temp[i] == (char) c)
			return ((char *)temp + i);
		if (i == 0)
			break ;
		i--;
	}
	if (temp[i] == (char) c)
		return ((char *)temp + i);
	return (0);
}
