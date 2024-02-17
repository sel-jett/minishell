/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:14:17 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/17 03:17:29 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*c_node(char *str, t_node *tail, int mode)
{
	t_node	*new_node;

	new_node = my_malloc(sizeof(t_node), 1);
	if (!new_node)
		return (0);
	new_node->value = str;
	new_node->next = 0;
	new_node->prev = tail;
	new_node->mode = mode;
	new_node->val_vide = 0;
	new_node->list_arg = 0;
	return (new_node);
}

t_list	*c_list(void)
{
	t_list	*new_list;

	new_list = my_malloc(sizeof(t_list), 1);
	if (!new_list)
		return (0);
	new_list->len = 0;
	new_list->top = NULL;
	return (new_list);
}

void	add_back(t_list *list, t_node *node)
{
	t_node	*tmp;

	if (!list)
		return ;
	if (!list->top)
	{
		list->top = node;
		list->tail = node;
		list->len++;
		return ;
	}
	tmp = list->top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	list->tail = node;
	list->tail->next = 0;
	list->len++;
}
