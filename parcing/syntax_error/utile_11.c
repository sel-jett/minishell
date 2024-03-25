/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:53:11 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 18:11:05 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handel_signel_(struct sigaction sa)
{
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	read_parse(int *index, t_list *list, t_env *exp, int *n)
{
	int	i;

	i = 0;
	while (list->str[i])
	{
		if (!plants(list, &i))
		{
			*index = 1;
			break ;
		}
	}
	if (!*index)
		if (!plant_4(list, exp, n))
			*index = 1;
}

void	ft_count(t_node *node, int *len, int *index)
{
	int	i;

	while (node && is_text2(node))
	{
		if (node->mode != TOKEN_EXPR)
			*index = 1;
		i = 0;
		while (node->value[i])
		{
			i++;
			(*len)++;
		}
		if (node->flage_space_ap == 1)
			break ;
		node = node->next;
	}
}

void	i_node_make(t_node *node, t_node **i_node)
{
	if (node && node->next && is_text(node->next))
		*i_node = node->next;
	else if (node && node->next && node->next->next
		&& is_text(node->next->next))
		*i_node = node->next->next;
}
