/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:52:54 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 09:10:55 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		(1) && (node = node->prev, node->next = 0);
	if (tmp->list_arg && tmp->list_arg->top)
	{
		new_node->list_arg = c_nlist();
		if (!new_node->list_arg)
			return (NULL);
		new_node->list_arg = tmp->list_arg;
	}
	return (new_node);
}

t_node_arbre	*parse_pipe(t_node **tmp)
{
	t_node_arbre	*node;

	node = parse_redir(tmp);
	if (!node)
		return (NULL);
	while (*tmp && (*tmp)->mode == TOKEN_PIPE)
	{
		*tmp = (*tmp)->next;
		node = new_node(TOKEN_PIPE, node, parse_redir(tmp));
		if (!node)
			return (NULL);
	}
	return (node);
}

t_node_arbre	*parse_and_or(t_node **tmp)
{
	t_node_arbre	*node;
	int				mode;

	node = parse_pipe(tmp);
	if (!node)
		return (NULL);
	while (*tmp && (((*tmp)->mode == TOKEN_OR) || ((*tmp)->mode == TOKEN_AND)))
	{
		mode = (*tmp)->mode;
		*tmp = (*tmp)->next;
		node = new_node(mode, node, parse_pipe(tmp));
		if (!node)
			return (NULL);
	}
	return (node);
}

int	plant_6(t_node *top, t_node_arbre **racine)
{
	*racine = parse_and_or(&top);
	if (!(*racine))
		return (0);
	return (1);
}

int	oxe5(t_node *tmp)
{
	if (tmp && (tmp->mode == TOKEN_PARENTHESE || is_text(tmp) || tmp->mode
			== TOKEN_SPACE || is_redir(tmp)))
		return (1);
	return (0);
}
