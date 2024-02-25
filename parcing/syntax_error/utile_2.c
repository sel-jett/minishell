/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/25 05:10:26 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node_arbre	*parse_cmd(t_node **tmp)
{
	t_node			*node;
	t_node_arbre	*arbre_node=NULL;
	
	if ((*tmp)->mode == TOKEN_PARENTHESE)
		//
	;
	if ((*tmp)->mode == TOKEN_EXPR)
	{
		node = *tmp;
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
			*tmp = (*tmp)->next;
		arbre_node = add_commade(node);
		if (!arbre_node)
			return (NULL);
		// if ((*tmp)->list_arg && (*tmp)->list_arg->top)
		// 		node->flag_expend = 1;
		return (arbre_node);
	}
	return	(NULL);
}
 
t_node_arbre	*parse_redir(t_node **tmp)
{
	t_node_arbre	*node_left;
	t_node_arbre	*node;

	node_left = parse_cmd(tmp);
	if (*tmp && ((*tmp)->mode == TOKEN_REDIR_APPEND || (*tmp)->mode ==
	 TOKEN_REDIR_IN || (*tmp)->mode == TOKEN_REDIR_OUT || (*tmp)->mode == TOKEN_HEREDOC))
	{
		node = c_node_arbre(*tmp);
		if (!node)
			return (0);
		node->list_redir = c_nlist();
		if (!node->list_redir)
			return (0);
		node->list_redir = (*tmp)->list_redir;
		node->left = node_left;
		*tmp = (*tmp)->next;
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
			*tmp = (*tmp)->next;
		return (node);
	}
	return (node_left);	
}

t_node_arbre	*new_node(int mode, t_node_arbre *left, t_node_arbre *right)
{
	t_node_arbre *node;

	if (!right)
		return (0);
	node = my_malloc(sizeof(t_node_arbre), 1);
	if (!node)
		return (NULL);
	node->mode = mode;
	node->left = left;
	node->right = right;
	return (node);
}

t_node_arbre	*parse_pipe(t_node **tmp)
{
	t_node_arbre *node;

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
	t_node_arbre *node;
	int 		mode;

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