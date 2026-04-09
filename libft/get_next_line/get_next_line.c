/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:37:36 by abuet             #+#    #+#             */
/*   Updated: 2026/04/09 12:57:57 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_remove_line(char *tab)
{
	char	*new_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i] && tab[i] != '\n')
		i++;
	if (!tab[i])
		return (free(tab), NULL);
	new_tab = malloc((ft_strlengnl(tab) - i + 1) * sizeof(char));
	if (!new_tab)
		return (NULL);
	i++;
	while (tab[i])
		new_tab[j++] = tab[i++];
	new_tab[j] = '\0';
	return (free(tab), new_tab);
}

static char	*ft_print_tab(char *tab)
{
	char	*new;
	int		i;

	i = 0;
	if (tab[i] == 0)
		return (NULL);
	while (tab[i] && tab[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (tab[i] && tab[i] != '\n')
	{
		new[i] = tab[i];
		i++;
	}
	if (tab[i] == '\n')
	{
		new[i] = '\n';
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*ft_alloc_tab(char *stat, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while ((!ft_strchrgnl(stat, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(stat), NULL);
		buffer[bytes_read] = '\0';
		stat = ft_strjoingnl(stat, buffer);
	}
	return (free(buffer), stat);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*print;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stat = ft_alloc_tab(stat, fd);
	if (!stat)
		return (NULL);
	print = ft_print_tab(stat);
	stat = ft_remove_line(stat);
	return (print);
}
