/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:58:32 by antoinebuet       #+#    #+#             */
/*   Updated: 2025/10/28 13:42:48 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size_d;
	size_t	size_s;

	size_s = ft_strlen(src);
	size_d = ft_strlen(dst);
	i = 0;
	if (size_d >= dstsize)
		return (dstsize + size_s);
	while (i + size_d < dstsize - 1 && src[i])
	{
		dst[i + size_d] = src[i];
		i++;
	}
	dst[size_d + i] = '\0';
	return (size_s + size_d);
}
