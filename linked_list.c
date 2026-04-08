/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:07:43 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/01 19:15:58 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_node *new_node(char *value)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

void add_first(t_node **list, char *value)
{
    t_node *new;

    new = new_node(value);
    if (!new)
        return ;
    new->next = *list;
    *list = new;
}


int lenght_list(t_node *head)
{
	t_node *current;
	int	size;

	size = 0;
	current = head;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void delete_first(t_node **head)
{
	t_node *tmp;

	if (!*head)
		return ;
	tmp = *head;
	*head = (*head)->next;
	free(tmp->value);
	free(tmp);
}

void reverse_list(t_node **list)
{
    t_node *prev;
    t_node *current;
    t_node *next;

    prev = NULL;
    current = *list;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *list = prev;
}