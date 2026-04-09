/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:27:08 by antoinebuet       #+#    #+#             */
/*   Updated: 2025/10/28 13:42:07 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ts;

	ts = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (ts[i] == (unsigned char) c)
			return (ts + i);
		i++;
	}
	return (0);
}
