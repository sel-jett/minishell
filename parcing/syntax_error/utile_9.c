/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:49:28 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 23:27:30 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_herdoc_0(t_node *tmp)
{
	char		*file;
	t_nnode		*i_node;

	(1) && (file = 0, i_node = 0);
	if (tmp->mode == TOKEN_HEREDOC)
		tmp->mode = TOKEN_REDIR_IN;
	i_node = tmp->list_redir->top;
	while (i_node)
	{
		if (i_node->mode == TOKEN_HEREDOC)
		{
			if (!open_herdoc(i_node, &file))
				return (0);
			if (i_node->next)
				i_node->next->value = file;
			i_node->value = "<";
			i_node->mode = TOKEN_REDIR_IN;
		}
		i_node = i_node->next;
	}
	return (1);
}

t_node_arbre	*parse_redir(t_node **tmp)
{
	t_node_arbre	*node_left;
	t_node_arbre	*node;

	node_left = parse_cmd(tmp);
	if (*tmp && is_redir(*tmp))
	{
		if (!open_herdoc_0(*tmp))
			return (0);
		node = c_node_arbre(*tmp);
		if (!node)
			return (NULL);
		node->list_redir = c_nlist();
		if (!node->list_redir)
			return (NULL);
		node->list_redir = (*tmp)->list_redir;
		(1) && (node->left = node_left, *tmp = (*tmp)->next);
		while ((*tmp) && (*tmp)->mode != TOKEN_PIPE && (*tmp)->mode
			!= TOKEN_AND && (*tmp)->mode != TOKEN_OR)
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

int	ope(t_node *node)
{
	if (!node)
		return (1);
	if (node->mode == TOKEN_AND || node->mode == TOKEN_OR
		|| node->mode == TOKEN_PIPE || is_redir(node))
		return (1);
	return (0);
}