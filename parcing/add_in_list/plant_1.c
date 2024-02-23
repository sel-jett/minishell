/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plant_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:00:33 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/23 21:37:35 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	fun_(t_list *list, int *i,char c,int mode)
{
	int		len;
	char	*s;
	t_node	*node;

	(1 == 1) && (len = 0, *i += 1,node = 0);
	while (list->str[*i + len] && list->str[*i + len] != c)
		len++;
	if (list->str[*i + len] != c)
		return (0);
	s = my_malloc (len * sizeof(char), 1);
	if (!s)
		return (0);
	len = 0;
	while (list->str[*i + len] && list->str[*i + len] != c)
	{
		s[len] = list->str[*i + len];
		len++;
	}
	s[len] = '\0';
	node = c_node(s, list->tail, mode,list);
	if (!node)
		return (0);
	add_back(list, node);
	*i += len + 1;
	return (1);
}

int	plant_1(t_list *list, int *i)
{
	if (list->str[*i] == '"')
	{
		if (!fun_(list, i, '"',TOKEN_Double_Q))
			return (0);
	}
	else if (list->str[*i] == '\'')
		if (!fun_(list, i, '\'',TOKEN_Single_Q))
			return (0);
	return (1);
}
