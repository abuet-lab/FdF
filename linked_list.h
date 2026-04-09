/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinebuet <antoinebuet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:37:17 by antoinebuet       #+#    #+#             */
/*   Updated: 2026/04/09 14:45:39 by antoinebuet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "fdf.h"

int		lenght_list(t_node *head);
char	*get_first(t_node *head);
void	delete_first(t_node **head);
void	reverse_list(t_node **list);
void	add_first(t_node **list, char *value);

#endif