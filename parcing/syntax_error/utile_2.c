/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/13 17:29:33 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node_arbre *new_sub(t_node_arbre *racine)
{
	t_node_arbre *node;

	node = my_malloc(sizeof(t_node_arbre), 1);
	if (!node)
		return (printf("facccck"),NULL);
	node->arbre = c_arbre();
	if (!node->arbre)
		return (printf("2\n"), NULL);
	node->arbre->racine = racine;
	node->mode = TOKEN_PARENTHESE;
	return (node);
}

t_node_arbre	*parse_parenthese(t_node **tmp)
{
	t_node_arbre *node;
	*tmp = (*tmp)->next;

	while ((*tmp)->value[0] != ')')
	{
		node = new_sub(parse_and_or(tmp));
		if (!node)
			return (printf("1\n"),NULL);
	}
	*tmp = (*tmp)->next;
	return (node);
}
t_node_arbre	*parse_cmd(t_node **tmp)
{
	t_node			*node;
	t_node_arbre	*arbre_node = NULL;

	if ((*tmp)->mode == TOKEN_PARENTHESE && (*tmp)->value[0] == '(')
		return (parse_parenthese(tmp));
	if ((*tmp)->mode == TOKEN_EXPR)
	{
		node = *tmp;
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
			*tmp = (*tmp)->next;
		arbre_node = add_commade(node);
		if (!arbre_node)
			return (printf("3\n"), NULL);
		return (arbre_node);
	}
	return	(printf("4\n"), NULL);
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
			return (printf("5\n"),NULL);
		node->list_redir = c_nlist();
		if (!node->list_redir)
			return (printf("6\n"),NULL);
		node->list_redir = (*tmp)->list_redir;
		// while(node->list_redir->top){
		// 	printf("[%s][%d]\n",node->list_redir->top->value,node->list_redir->top->avant_);
		// 	node->list_redir->top = node->list_redir->top->next;
		// 	}
		// exit(0);
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
		return (printf("7\n"), NULL);
	node = my_malloc(sizeof(t_node_arbre), 1);
	if (!node)
		return (printf("8\n"), NULL);
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
		return (printf("9\n"), NULL);
	while (*tmp && (*tmp)->mode == TOKEN_PIPE)
	{
		*tmp = (*tmp)->next;
		node = new_node(TOKEN_PIPE, node, parse_redir(tmp));
		if (!node)
			return (printf("10\n"),NULL);
	}
	return (node);
}

t_node_arbre	*parse_and_or(t_node **tmp)
{
	t_node_arbre *node;
	int 		mode;

	node = parse_pipe(tmp);
	if (!node)
		return (printf("11\n"),NULL);
	while (*tmp && (((*tmp)->mode == TOKEN_OR) || ((*tmp)->mode == TOKEN_AND)))
	{
		mode = (*tmp)->mode;
		*tmp = (*tmp)->next;
		node = new_node(mode, node, parse_pipe(tmp));
		if (!node)
			return (printf("12\n"),NULL);
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
