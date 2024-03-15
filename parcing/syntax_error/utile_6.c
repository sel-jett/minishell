/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:19:27 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/15 03:20:41 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	plant_5(t_node	*tmp, t_list *list)
{
	t_node	*node;
	int		index;

	node = 0;
	if (!list)
		return (0);
	while (tmp)
	{
		index = 0;
		if (tmp->mode != TOKEN_SPACE)
		{
			check_wilc(tmp);
			node = c_cpynode(tmp, list->tail, list);
			if (!node)
				return (0);
			add_back(list, node);
		}
		if (tmp->next && tmp->next->mode == TOKEN_SPACE)
			node->flag_space = 1;
		if (!tmp->next)
			node->flag_space = 1;
		if (tmp->list_arg && tmp->list_arg->top)
			node->flag_expend = 1;
		tmp = tmp->next;
	}
	tmp = list->top;
	while (tmp)
	{
		if (tmp->mode == TOKEN_Double_Q || tmp->mode == TOKEN_Single_Q)
		{
			if (tmp->mode == TOKEN_Double_Q)
				if (tmp->list_arg && tmp->list_arg->top)
					node->flag_expend = 1;
			tmp->mode = TOKEN_EXPR;
		}
		tmp = tmp->next;
	}
	return (1);
}
