/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:23:47 by antoinebuet       #+#    #+#             */
/*   Updated: 2025/10/28 13:43:16 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static size_t	check_front(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
			j++;
		if (set[j] == '\0')
			return (i);
		i++;
	}
	return (i);
}

static size_t	check_end(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	c;

	len = ft_strlen(s1);
	i = len;
	while (i > 0)
	{
		j = 0;
		c = s1[i - 1];
		while (set[j] && set[j] != c)
			j++;
		if (set[j] == '\0')
			return (len - i);
		i--;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	end;
	size_t	i;
	char	*newstring;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	front = check_front(s1, set);
	end = check_end(s1, set);
	if (front + end >= ft_strlen(s1))
		return (ft_strdup(""));
	newstring = malloc((ft_strlen(s1) - (front + end) + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	while (front < (ft_strlen(s1) - end))
		newstring[i++] = s1[front++];
	newstring[i] = '\0';
	return (newstring);
}
