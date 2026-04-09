/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:05:53 by antoinebuet       #+#    #+#             */
/*   Updated: 2025/10/07 12:10:45 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;
	unsigned char	zero;

	zero = '\0';
	temp = (unsigned char *) s;
	while (n > 0)
	{
		*temp++ = zero;
		n--;
	}
}
