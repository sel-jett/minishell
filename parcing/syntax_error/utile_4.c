/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:32:37 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/16 01:35:24 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_text(t_node *tmp)
{
	if (tmp->mode == TOKEN_EXPR || tmp->mode == TOKEN_Double_Q
		|| tmp->mode == TOKEN_Single_Q)
		return (1);
	return (0);
}

int	check_syntax_2(t_node *tmp)
{
	if (tmp && tmp->prev)
		if (tmp->prev->mode != TOKEN_SPACE && (is_text(tmp->prev)
				|| tmp->prev->value[0] == ')'))
			return (1);
	if (tmp && tmp->prev && tmp->prev->mode == TOKEN_SPACE && tmp->prev->prev)
		if (tmp->prev->prev->mode != TOKEN_SPACE
			&& (is_text(tmp->prev->prev) || tmp->prev->prev->value[0] == ')'))
			return (1);
	return (0);
}

int	check_syntax_4(t_node *tmp)
{
	if (!add_list_redir(tmp))
		return (0);
	if (tmp && tmp->next)
		if (tmp->next->mode != TOKEN_SPACE && (is_text(tmp->next)
				|| tmp->next->value[0] == '(' || is_redir(tmp->next)))
			return (1);
	if (tmp && tmp->next && tmp->next->mode == TOKEN_SPACE && tmp->next->next)
		if (tmp->next->next->mode != TOKEN_SPACE && (is_text(tmp->next->next)
				|| tmp->next->next->value[0] == '('
				|| is_redir(tmp->next->next)))
			return (1);
	return (0);
}

int	check_syntax_1(t_node *tmp)
{
	if (!add_list_redir(tmp))
		return (0);
	if (tmp && tmp->next)
		if (tmp->next->mode != TOKEN_SPACE && (is_text(tmp->next)
				|| tmp->next->value[0] == '('))
			return (1);
	if (tmp && tmp->next && tmp->next->mode== TOKEN_SPACE && tmp->next->next)
		if (tmp->next->next->mode != TOKEN_SPACE && (is_text(tmp->next->next)
				|| tmp->next->next->value[0] == '('))
			return (1);
	return (0);
}

int	check_syntax_3(t_node *tmp)
{
	char	*str;
	int		i;

	(1) && ((str = tmp->value) && (i = 0));
	tmp->list_arg = c_nlist();
	if (!tmp->list_arg)
		return (0);
	while (str && str[i])
	{
		while (str && str[i] && str[i] == '$')
		{
			i++;
			if (str && str[i] && !add_args(tmp->list_arg, &str[i], &i))
				return (0);
		}
		if (str[i])
			i++;
	}
	// if (tmp->list_arg && tmp->list_arg->top)
	// {
	// 	while (tmp->list_arg->top)
	// 	{
	// 		printf("[%s]\n",tmp->list_arg->top->value);
	// 		tmp->list_arg->top = tmp->list_arg->top->next; 
	// 	}
	// }
	// exit(0);
	return (1);
}
