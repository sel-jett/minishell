/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plant_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:06:53 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 09:29:57 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_two( t_list *list, int *i, int mode)
{
	char	*s;
	int		j;
	t_node	*node;

	(1 == 1) && (j = -1, s = 0, node = 0);
	s = my_malloc(sizeof(char) * 3, 1);
	if (!s)
		return (0);
	while (++j < 2)
		s[j] = list ->str[*i + j];
	s[j] = '\0';
	node = c_node(s, list->tail, mode, list);
	if (!node)
		return (0);
	add_back(list, node);
	*i += 2;
	return (1);
}

int	add_one(t_list *list, int *i, int mode)
{
	char	*s;
	t_node	*node;

	(1 == 1) && (s = 0, node = 0);
	s = my_malloc(sizeof(char) * 2, 1);
	if (!s)
		return (0);
	(1) && ((s[0] = list->str[*i]) && (s[1] = '\0'));
	node = c_node(s, list->tail, mode, list);
	if (!node)
		return (0);
	add_back(list, node);
	(*i)++;
	return (1);
}
