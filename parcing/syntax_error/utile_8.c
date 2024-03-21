/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:19:01 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 08:37:53 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	plant_4(t_list *list)
{
	t_node	*tmp;
	int		count_parentheses;

	count_parentheses = 0;
	if (list && list->top)
	{
		(1) && (tmp = list->top, list->top->prev = 0);
		while (tmp)
		{
			check_wilc(tmp);
			if (tmp->mode == TOKEN_PARENTHESE && tmp->value[0] == '(')
			{
				count_parentheses++;
				if (!check_enter_parentheses(tmp))
					return (affichage(1), ft_status(258, 1), 0);
			}
			else if (tmp->mode == TOKEN_PARENTHESE && tmp->value[0] == ')'
				&& count_parentheses == 0)
				return (affichage(2), ft_status(258, 1), 0);
			else if (tmp->mode == TOKEN_PARENTHESE && tmp->value[0] == ')'
				&& count_parentheses >= 1)
			{
				count_parentheses--;
				if (!check_apres_parentheses(tmp))
					return (affichage(3), ft_status(258, 1), 0);
			}
			else if (tmp->mode == TOKEN_OR || tmp->mode
				== TOKEN_AND || tmp->mode == TOKEN_PIPE)
			{
				if (!check_syntax_2(tmp))
					return (affichage(4), ft_status(258, 1), 0);
				if (!check_syntax_4(tmp))
					return (affichage(5), ft_status(258, 1), 0);
			}
			if (is_redir(tmp))
			{
				if (!check_syntax_1(tmp))
					return (affichage(6), ft_status(258, 1), 0);
			}
			if (tmp->mode == TOKEN_Double_Q || tmp->mode == TOKEN_EXPR)
			{
				if (!check_syntax_3(tmp))
					return (0);
				if (tmp->mode == TOKEN_EXPR)
					if (!check_exp(tmp))
						return (affichage(7), ft_status(258, 1), 0);
			}
			tmp = tmp->next;
		}
	}
	if (count_parentheses != 0)
		return (affichage(8), ft_status(258, 1), 0);
	return (1);
}

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
			node = c_cpynode(tmp, list->tail, list);
			if (!node)
				return (0);
			check_wilc(node);
			add_back(list, node);
		}
		if ((tmp->prev && tmp->prev->mode == TOKEN_SPACE)
			&& tmp->prev->prev && !ope(tmp->prev->prev))
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
			{
				tmp->flag_quote = 1;
				if (tmp->list_arg && tmp->list_arg->top)
					node->flag_expend = 1;
			}
			if (tmp->mode == TOKEN_Single_Q)
				tmp->flag_quote = 2;
			tmp->mode = TOKEN_EXPR;
		}
		tmp = tmp->next;
	}
	return (1);
}
