/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:19:01 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 08:19:02 by amel-has         ###   ########.fr       */
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