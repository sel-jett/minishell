/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:19:17 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/13 15:30:18 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_empty(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\v' && str[i] != '\f' && str[i] != '\v')
			return (0);
		i++;
	}
	return (1);
}

int	check_enter_parentheses(t_node *node)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	if (node && node->prev  && node->prev->mode == TOKEN_SPACE)
	{
		if (node && node->prev && node->prev->prev && (node->prev->prev->mode
		== TOKEN_EXPR || node->prev->prev->mode == TOKEN_Double_Q || node->prev->prev->mode
		== TOKEN_Single_Q || node->prev->prev->mode == TOKEN_PARENTHESE || node->prev->prev->mode ==
		TOKEN_REDIR_APPEND || node->prev->prev->mode == TOKEN_REDIR_IN ||  node->prev->prev->mode ==
		TOKEN_REDIR_OUT || node->prev->prev->mode == TOKEN_HEREDOC))
			return (printf("haa ana 1\n"),0);
	}
	else if ((node && node->prev)  && (node->prev->mode == TOKEN_EXPR || node->prev->mode == TOKEN_Single_Q || node->prev->mode ==
	TOKEN_Double_Q || node->prev->mode == TOKEN_REDIR_APPEND || node->prev->mode ==
	TOKEN_REDIR_OUT|| node->prev->mode == TOKEN_REDIR_IN || node->prev->mode == TOKEN_HEREDOC))
		return (printf("haa ana 2\n"),0);
	if (node && node->next)
		node = node->next;
	while (node && node->value[0] != ')')
	{
		if (is_empty(node->value))
			j++;
		i++;
		node = node->next;
	}
	if (i == j)
		return (printf("haa ana 3\n"),0);
	if (i)
		return (1);
	return (printf("ha ana 4"),0);
}

int	check_apres_parentheses(t_node *node)
{
	if (node && node->next  && node->next->mode == TOKEN_SPACE)
	{
		if (node && node->next && node->next->next && (node->next->next->mode
		== TOKEN_EXPR || node->next->next->mode == TOKEN_Double_Q || node->next->next->mode
		== TOKEN_Single_Q || (node->next->next->mode == TOKEN_PARENTHESE && node->next->next->value[0] == '(')))
			return (0);
	}
	else if ( (node && node->next)  && (node->next->mode == TOKEN_EXPR || node->next->mode == TOKEN_Single_Q ||  node->next->mode ==
	TOKEN_Double_Q || (node->next->mode == TOKEN_PARENTHESE && node->next->value[0] == '(')))
		return (0);
	return (1);
}

void	checkSinglQ(t_node *tmp)
{
	if (!tmp-> value[0])
		tmp->val_vide = 1;
}

int check_exp(t_node *tmp)
{
	int i = 0;
	while (tmp->value && tmp->value[i])
	{
		if (tmp->value[i] != '!')
			return (1);
		i++;
	}
	if (tmp->prev && tmp->prev->value && tmp->prev->value[0] == '(')
		return (1);
	return (0);
}
int	plant_4(t_list *list)
{
	t_node	*tmp;
	int		count_parentheses = 0;
	if (list && list->top)
	{
		(1 == 1) && (tmp = list->top, list->top->prev = NULL);
		while (tmp)
		{
			if (tmp->mode == TOKEN_PARENTHESE  && tmp->value[0] == '(')
			{
				count_parentheses++;
				if (!check_enter_parentheses(tmp))
					return (printf("syntax error 0!\n"), 0);
			}
			else if (tmp->mode == TOKEN_PARENTHESE  && tmp->value[0] == ')' && count_parentheses == 0)
				return (printf("syntax error 1!\n"), 0);
			else if (tmp->mode == TOKEN_PARENTHESE  && tmp->value[0] == ')' && count_parentheses >= 1)
			{
				count_parentheses--;
				if (!check_apres_parentheses(tmp))
					return (printf("syntax error 2!\n"), 0);
			}
			else if (tmp->mode == TOKEN_OR || tmp->mode
				== TOKEN_AND || tmp->mode == TOKEN_PIPE)
			{
				if (!check_syntax_2(tmp) || !check_syntax_4(tmp))
					return (printf("syntax error 3!\n"), 0);
			}
			if (tmp->mode == TOKEN_REDIR_APPEND || tmp->mode
				== TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT
				|| tmp->mode == TOKEN_HEREDOC)
			{
				if (!check_syntax_1(tmp))
					return (printf("syntax error 4!\n"), 0);
			}
			if (tmp->mode == TOKEN_Double_Q || tmp->mode == TOKEN_EXPR)
			{
				if (!check_syntax_3(tmp))
					return (printf("syntax error 5!\n"), 0);
				if (tmp->mode == TOKEN_EXPR)
					if (!check_exp(tmp))
						return (printf("syntax error 6!\n"), 0);
			}
			else if(tmp->mode == TOKEN_Single_Q)
				checkSinglQ(tmp);
			tmp = tmp->next;
		}
	}
	if (count_parentheses != 0)
		return (printf("syntax error 6 [%d]\n",count_parentheses), 0);
	return (1);
}
