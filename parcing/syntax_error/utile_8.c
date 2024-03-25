/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:19:01 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 00:25:00 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	plant4_oxe1(int *count_parentheses, t_node *tmp)
{
	if (tmp->mode == TOKEN_PARENTHESE && tmp->value[0] == '(')
	{
		(*count_parentheses)++;
		if (!check_enter_parentheses(tmp))
			return (affichage(1), ft_status(258, 1), 0);
	}
	else if (tmp->mode == TOKEN_PARENTHESE && tmp->value[0] == ')'
		&& (*count_parentheses) == 0)
		return (affichage(2), ft_status(258, 1), 0);
	else if (tmp->mode == TOKEN_PARENTHESE && tmp->value[0] == ')'
		&& (*count_parentheses) >= 1)
	{
		(*count_parentheses)--;
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
	return (1);
}

static int	plant4_oxe2(t_node *tmp, t_env *exp, int *n)
{
	if (is_redir(tmp))
	{
		if (!check_syntax_1(tmp, exp, n))
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
	return (1);
}

int plant_4(t_list *list, t_env *exp, int *n)
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
			if (!plant4_oxe1(&count_parentheses, tmp))
				return (0);
			if (!plant4_oxe2(tmp, exp, n))
				return (0);
			tmp = tmp->next;
		}
	}
	if (count_parentheses != 0)
		return (affichage(8), ft_status(258, 1), 0);
	return (1);
}

static void	plant5_oxe1(t_node	*tmp, t_node *node)
{
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
}

int	plant_5(t_node	*tmp, t_list *list)
{
	t_node	*node;

	node = 0;
	if (!list)
		return (0);
	while (tmp)
	{
		if (tmp->mode != TOKEN_SPACE)
		{
			node = c_cpynode(tmp, list->tail, list);
			if (!node)
				return (0);
			(1) && (check_wilc(node), add_back(list, node), 0);
		}
		if ((tmp->prev && tmp->prev->mode == TOKEN_SPACE)
			&& tmp->prev->prev && !ope(tmp->prev->prev))
			node->flag_space = 1;
		if (tmp->list_arg && tmp->list_arg->top)
		{
			node->flag_expend = 1;
			(tmp->mode == TOKEN_EXPR) && (node->flag_expend = 2);
		}
		tmp = tmp->next;
	}
	return (plant5_oxe1(list->top, node), 1);
}
