#ifndef LINKED_LIST_H
# define LINKED_LIST_H

#include "fdf.h"

void add_back(t_node **head, char *value);
int lenght_list(t_node *head);
char *get_first(t_node *head);
void delete_first(t_node **head);
void reverse_list(t_node **list);
void add_first(t_node **list, char *value);

#endif