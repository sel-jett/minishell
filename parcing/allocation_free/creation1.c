/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:13:42 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/15 02:47:43 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*c_node(char *str, t_node *tail, int mode, t_list *list)
{
	t_node	*new_node;

	new_node = my_malloc(sizeof(t_node), 1);
	if (!new_node)
		return (0);
	new_node->value = str;
	new_node->next = 0;
	new_node->prev = tail;
	new_node->mode = mode;
	new_node->list_arg = 0;
	new_node->list_redir = 0;
	new_node->flag_expend = 0;
	new_node->flag_space = 0;
	new_node->flag_wilc = 0;
	new_node->list = list;
	new_node->avant_ = 0;
	return (new_node);
}

t_node	*c_cpynode(t_node *node, t_node *tail, t_list *list)
{
	t_node	*new_node;

	new_node = my_malloc(sizeof(t_node), 1);
	if (!new_node)
		return (0);
	new_node->value = node->value;
	new_node->next = 0;
	new_node->prev = tail;
	new_node->mode = node->mode;
	new_node->list_arg = node->list_arg;
	new_node->list_redir = node->list_redir;
	new_node->flag_expend = 0;
	new_node->flag_space = 0;
	new_node->flag_wilc = node->flag_wilc;
	new_node->avant_ = node->avant_;
	new_node->list = list;
	return (new_node);
}

t_list	*c_list(void)
{
	t_list	*new_list;

	new_list = my_malloc(sizeof(t_list), 1);
	if (!new_list)
		return (0);
	new_list->top = 0;
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
		return ;
	}
	tmp = list->top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	list->tail = node;
	list->tail->next = 0;
}
