/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:14:17 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/18 23:45:47 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_back_arg(t_list_arg *list, t_node_arg *node)
{
	t_node_arg	*tmp;

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

t_node_arg	*c_node_arg(char *str)
{
	t_node_arg	*new_node_arg;

	new_node_arg = my_malloc(sizeof(t_node_arg), 1);
	if (!new_node_arg)
		return (0);
	new_node_arg->value = str;
	new_node_arg->next = 0;
	return (new_node_arg);
}

t_list_arg	*c_list_arg(void)
{
	t_list_arg	*new_arg;

	new_arg = my_malloc(sizeof(t_list_arg), 1);
	if (!new_arg)
		return (0);
	new_arg->top = 0;
	new_arg->tail = 0;
	new_arg->len = 0;
	return (new_arg);
}
