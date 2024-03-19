/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:22:32 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/19 06:06:40 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_list_redir(t_node *node)
{
	t_node	*tmp;
	t_node	*tmp1;
	t_nnode	*redir_node;
	int i = 0;

	(1) && (tmp = node, redir_node = NULL, tmp1 = NULL);
	node->list_redir = c_nlist();
	if (!node->list_redir)
		return (0);
	if (node && node->prev)
	{
		tmp1 = node->prev;
		while (tmp1->prev && (tmp1->prev->mode != TOKEN_AND
				&& tmp1->prev->mode != TOKEN_OR
				&& tmp1->prev->mode != TOKEN_PIPE))
			tmp1 = tmp1->prev;
		while (tmp1 && !is_redir(tmp1))
		{
			if (tmp1->mode != TOKEN_SPACE)
			{
				tmp1->avant_ = 1;
				redir_node = c_nnode(tmp1);
				if (!redir_node)
					return (0);
				if (tmp1->prev && tmp1->prev->mode == TOKEN_SPACE && tmp1->prev->prev && !ope(tmp1->prev->prev))
					redir_node->flag_space = 1;
				add_nback(node->list_redir, redir_node);
			}
			tmp1 = tmp1->next;
		}
	}
	// tmp = tmp->next;
	if (tmp && tmp->mode == TOKEN_SPACE)
		tmp = tmp->next;
	while (tmp && (tmp->mode == TOKEN_PARENTHESE || is_text(tmp) || tmp->mode
			== TOKEN_SPACE || is_redir(tmp)))
	{
		i = 0;
		while (tmp->value && tmp->value[i])
		{
			if (tmp->value  && tmp->value[i] == '$')
			{
				tmp->flag_expend = 1;
				if (tmp->mode == TOKEN_EXPR)
					tmp->flag_expend = 2;
			}
			i++;
		}
		if (tmp->mode != TOKEN_SPACE)
		{
			if (tmp->prev && tmp->prev->prev
				&& is_redir(tmp->prev->prev) && is_text(tmp))
			{
				tmp->avant_ = 2;
				if (tmp->prev->prev->mode == TOKEN_REDIR_IN || tmp->prev->prev->mode == TOKEN_HEREDOC)
					tmp->avant_ = 3;
				if (tmp->prev->prev->mode == TOKEN_REDIR_APPEND)
					tmp->avant_ = 4;
			}
			else if (tmp->prev && is_redir(tmp->prev) && is_text(tmp))
			{
				tmp->avant_ = 2;
				if (tmp->prev->mode == TOKEN_REDIR_IN || tmp->prev->mode == TOKEN_HEREDOC)
					tmp->avant_ = 3;
				if (tmp->prev->mode == TOKEN_REDIR_APPEND)
					tmp->avant_ = 4;
			}
			redir_node = c_nnode(tmp);
			if (!redir_node)
				return (0);
			if (tmp->prev && tmp->prev->mode == TOKEN_SPACE && !ope(tmp->prev->prev)) 
			{
				// if (tmp)
				redir_node->flag_space = 1;
			}
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
	// t_node *x = new_node->list->top;
	// while(x)
	// {
	// 	// check_wilc(x);
	// 	printf("[%d]->",x->flag_wilc);
	// 	x = x->next;
	// }
	// exit(1);
	node = tmp;
	while (node && (node->mode == TOKEN_EXPR))
		node = node->next;
	if (node)
	{
		node = node->prev;
		node->next = NULL;
	}
	if (tmp->list_arg && tmp->list_arg->top)
	{
		new_node->list_arg = c_nlist();
		if (!new_node->list_arg)
			return (NULL);
		new_node->list_arg = tmp->list_arg;
	}
	// t_node *x = new_node->list->top ;
	// while(x)
	// {
	// 	printf("[%s]->",x->value);
	// 	x = x->next;
	// }
	// printf("\n");
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
