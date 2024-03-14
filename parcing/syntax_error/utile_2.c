/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/14 20:37:16 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node_arbre	*new_sub(t_node_arbre *racine)
{
	t_node_arbre	*node;

	node = my_malloc(sizeof(t_node_arbre), 1);
	if (!node)
		return (NULL);
	node->arbre = c_arbre();
	if (!node->arbre)
		return (NULL);
	node->arbre->racine = racine;
	node->mode = TOKEN_PARENTHESE;
	return (node);
}

t_node_arbre	*parse_parenthese(t_node **tmp)
{
	t_node_arbre	*node;

	*tmp = (*tmp)->next;
	while ((*tmp)->value[0] != ')')
	{
		node = new_sub(parse_and_or(tmp));
		if (!node)
			return (NULL);
	}
	*tmp = (*tmp)->next;
	return (node);
}

t_node_arbre	*parse_cmd(t_node **tmp)
{
	t_node			*node;
	t_node_arbre	*arbre_node;

	arbre_node = NULL;
	if ((*tmp)->mode == TOKEN_PARENTHESE && (*tmp)->value[0] == '(')
		return (parse_parenthese(tmp));
	if ((*tmp)->mode == TOKEN_EXPR)
	{
		node = *tmp;
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
			*tmp = (*tmp)->next;
		arbre_node = add_commade(node);
		if (!arbre_node)
			return (NULL);
		return (arbre_node);
	}
	return (NULL);
}

t_node_arbre	*parse_redir(t_node **tmp)
{
	t_node_arbre	*node_left;
	t_node_arbre	*node;

	node_left = parse_cmd(tmp);
	if (*tmp && is_redir(*tmp))
	{
		node = c_node_arbre(*tmp);
		if (!node)
			return (NULL);
		node->list_redir = c_nlist();
		if (!node->list_redir)
			return (NULL);
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
	t_node_arbre	*node;

	if (!right)
		return (NULL);
	node = my_malloc(sizeof(t_node_arbre), 1);
	if (!node)
		return (NULL);
	node->mode = mode;
	node->left = left;
	node->right = right;
	return (node);
}
