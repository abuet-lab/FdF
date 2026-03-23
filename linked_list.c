/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:07:43 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/03/16 17:52:43 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_node *new_node(char *value)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	node->value = value;
	node->next = NULL;
	return (node);
}

void add_back(t_node **head, char *value)
{
	t_node *current;

	if(!*head)
	{
		*head = new_node(value);
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node(value);
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

char *get_first(t_node *head)
{
	if (!head)
		return (0);
	return (head->value);
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