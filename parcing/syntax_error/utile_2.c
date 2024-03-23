/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/23 02:00:27 by amel-has         ###   ########.fr       */
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

	arbre_node = 0;
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

bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
