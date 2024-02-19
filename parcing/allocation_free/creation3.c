/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:24:24 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/18 23:29:17 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	add_back_redir(t_list_redir *list, t_node_redir *node)
{
	t_node_redir	*tmp;

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

t_node_redir	*c_node_redir(char *str)
{
	t_node_redir	*new_node_redir;

	new_node_redir = my_malloc(sizeof(t_node_redir), 1);
	if (!new_node_redir)
		return (0);
	new_node_redir->value = str;
	new_node_redir->next = 0;
	return (new_node_redir);
}

t_list_redir	*c_list_redir(void)
{
	t_list_redir	*new_redir;

	new_redir = my_malloc(sizeof(t_list_redir), 1);
	if (!new_redir)
		return (0);
	new_redir->top = 0;
	new_redir->tail = 0;
	new_redir->len = 0;
	return (new_redir);
}