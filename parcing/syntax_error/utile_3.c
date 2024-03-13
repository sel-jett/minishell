/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:22:32 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/13 03:52:55 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_list_redir(t_node *node)
{
	t_node          *tmp;
	t_nnode    		*redir_node;

	(1 == 1) && (tmp = node, redir_node = NULL);
	node->list_redir = c_nlist();
	if (!node->list_redir)
		return (0);
	tmp = tmp->next;
	if (tmp && tmp->mode == TOKEN_SPACE)
		tmp = tmp->next;
	while (tmp && (tmp->mode == TOKEN_EXPR || tmp->mode 
	== TOKEN_PARENTHESE || tmp->mode == TOKEN_Double_Q || tmp->mode 
	== TOKEN_Single_Q || tmp->mode == TOKEN_SPACE || tmp->mode== TOKEN_HEREDOC || tmp->mode== TOKEN_REDIR_APPEND || tmp->mode == TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT))
	{
	 	if (tmp->mode != TOKEN_SPACE)
		{
			redir_node =  c_nnode(tmp->value);
			if (!redir_node)
				return (0);
			add_nback(node->list_redir, redir_node);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_node_arbre	*add_commade(t_node	*tmp)
{
	t_node_arbre	*new_node;
	t_node			*node;

	new_node = c_node_arbre(tmp);
	if (!new_node)
		return (0);
	new_node->list = c_list();
	if (!new_node->list)
		return (0);
	new_node->list->top = tmp;
	node = tmp;
	while (node && (node->mode == TOKEN_EXPR))
			node = node->next;
	if (node)
	{
		node = node->prev;
		node->next  = NULL;
	}
	if (tmp->list_arg && tmp->list_arg->top)
	{
		new_node->list_arg = c_nlist();
		if (!new_node->list_arg)
			return (NULL);
		new_node->list_arg = tmp->list_arg;
	}
	return (new_node);
}
