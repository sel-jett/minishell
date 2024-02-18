/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plant_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:04:14 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/17 23:58:21 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check(int c)
{
	if (c && c != '|' && c != '&' && c != '<'
		&& c != '>' && c != '&'  && c != ' ' && c != '"' && c != ')' && c != '\'' && c != '(')
		return (1);
	return (0);
}

int	plant_2(t_list *list, int *i)
{
	int		len;
	char	*s;
	t_node	*node;

	(1 == 1) && (len = 0, node = 0, s = 0);
	while (check(list->str[*i + len]))
		len++;
	s = my_malloc(sizeof(char) * (len + 1), 1);
	if (!s)
		return (0);
	(1 == 1) && (len = -1);
	while (check(list->str[++len + *i]))
		s[len] = list->str[*i + len];
	s[len] = '\0';
	node = c_node(s, list->tail, TOKEN_EXPR);
	if (!node)
		return (0);
	add_back(list, node);
	*i += len;
	return (1);
}
