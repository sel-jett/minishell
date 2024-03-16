/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:19:27 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/16 06:33:42 by sel-jett         ###   ########.fr       */
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
		if (tmp->prev && tmp->prev->mode == TOKEN_SPACE)
			node->flag_space = 1;
		if (tmp->list_arg && tmp->list_arg->top)
		{
			node->flag_expend = 1;
			if (tmp->mode == TOKEN_EXPR)
				node->flag_expend = 2;
		}
		tmp = tmp->next;
	}
	tmp = list->top;
	while (tmp)
	{
		if (tmp->mode == TOKEN_Double_Q || tmp->mode == TOKEN_Single_Q)
		{
			if (tmp->mode == TOKEN_Double_Q)
				if (tmp->list_arg && tmp->list_arg->top)
				{
					// printf("je suis la");
					node->flag_expend = 1;
				}
			tmp->mode = TOKEN_EXPR;
		}
		tmp = tmp->next;
	}
	return (1);
}
