/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuet <abuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:58:31 by antoinebuet       #+#    #+#             */
/*   Updated: 2025/10/28 13:40:17 by abuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static size_t	number_string(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static size_t	number_caractere(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count])
		count++;
	return (count);
}

static void	free_array(char **array, size_t n)
{
	while (n > 0)
	{
		free(array[n - 1]);
		n--;
	}
	free(array);
}

const char	*forward_pointer(char const *s, char c)
{
	while (*s && *s == c)
	{
		s++;
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	size_t	tab1;
	size_t	tab2;
	size_t	words;
	char	**split;

	tab1 = 0;
	if (!s)
		return (NULL);
	split = malloc((number_string(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	words = number_string(s, c);
	while (tab1 < words)
	{
		s = forward_pointer(s, c);
		tab2 = number_caractere(s, c);
		split[tab1] = malloc((tab2 + 1) * sizeof(char));
		if (!split[tab1])
			return (free_array(split, tab1), NULL);
		ft_strlcpy(split[tab1], s, tab2 + 1);
		s += tab2;
		tab1++;
	}
	split[tab1] = NULL;
	return (split);
}
