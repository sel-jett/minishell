/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:22:32 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/13 17:23:00 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_list_redir(t_node *node)
{
	t_node          *tmp;
	t_node          *tmp1;
	t_nnode    		*redir_node;

	(1 == 1) && (tmp = node, redir_node = NULL ,tmp1 = NULL);
	node->list_redir = c_nlist();
	if (!node->list_redir)
		return (0);
	if (node && node->prev)
	{
		tmp1 = node->prev;
		while (tmp1->prev && (tmp1->prev->mode != TOKEN_AND && tmp1->prev->mode != TOKEN_OR && tmp1->prev->mode != TOKEN_PIPE))
			tmp1 = tmp1->prev;
		while (tmp1 && !is_redir(tmp1))
		{
			if (tmp1->mode != TOKEN_SPACE)
			{
				tmp1->avant_ = 1;
				redir_node =  c_nnode(tmp1);
				if (!redir_node)
					return (0);
				add_nback(node->list_redir, redir_node);
			}
			tmp1 = tmp1->next;
		}
	}
	tmp = tmp->next;
	if (tmp && tmp->mode == TOKEN_SPACE)
		tmp = tmp->next;
	while (tmp && (tmp->mode == TOKEN_PARENTHESE  || is_text(tmp) || tmp->mode 
	== TOKEN_SPACE || is_redir(tmp)))
	{
	 	if (tmp->mode != TOKEN_SPACE)
		{
			if (tmp->prev && tmp->prev->prev && is_redir(tmp->prev->prev) && is_text(tmp))
				tmp->avant_ = 2;
			else if(tmp->prev && is_redir(tmp->prev) && is_text(tmp)){
				tmp->avant_ = 2;
			}
			redir_node =  c_nnode(tmp);
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
