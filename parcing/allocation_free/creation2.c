/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:14:17 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/25 02:13:59 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_nback(t_nlist *list, t_nnode *node)
{
	t_nnode	*tmp;

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

t_nnode	*c_nnode(char *str)
{
	t_nnode	*new_nnode;

	new_nnode = my_malloc(sizeof(t_nnode), 1);
	if (!new_nnode)
		return (0);
	new_nnode->value = str;
	new_nnode->next = 0;
	return (new_nnode);
}

t_nlist	*c_nlist(void)
{
	t_nlist	*new;

	new = my_malloc(sizeof(t_nlist), 1);
	if (!new)
		return (0);
	new->top = 0;
	new->tail = 0;
	new->len = 0;
	return (new);
}
