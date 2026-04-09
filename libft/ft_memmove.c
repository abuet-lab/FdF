/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:07:02 by antoinebuet       #+#    #+#             */
/*   Updated: 2025/10/28 13:42:18 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tdst;
	const char	*tsrc;

	if (dst == src)
		return (dst);
	tdst = (char *) dst;
	tsrc = (const char *) src;
	if (tdst <= tsrc || tdst >= tsrc + len)
	{
		while (len--)
			*tdst++ = *tsrc++;
	}
	else
	{
		tdst += len;
		tsrc += len;
		while (len--)
			*--tdst = *--tsrc;
	}
	return (dst);
}
