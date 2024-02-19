/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:19:17 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/19 06:41:54 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_syntax_2(t_node *tmp)
{
	if (tmp && tmp->prev)
		if (!is_empty(tmp->prev->value) && (tmp->prev->mode == TOKEN_EXPR || tmp->prev->mode
			== TOKEN_Double_Q || tmp->prev->mode == TOKEN_Single_Q || tmp->prev->value[0] == ')'))
			return (1);
	if (tmp && tmp->prev && tmp->prev->prev)
		if (!is_empty(tmp->prev->prev->value) && (tmp->prev->prev->mode == TOKEN_EXPR
			|| tmp->prev->prev->mode == TOKEN_Double_Q || tmp->prev->prev->mode
			== TOKEN_Single_Q || tmp->prev->prev->value[0] == ')'))
			return (1);
	return (0);
}
// static int	check_syntax_2(t_node *tmp)
// {
// 	if (tmp && tmp->prev)
// 		if (!is_empty(tmp->prev->value) && (tmp->prev->mode == TOKEN_EXPR || tmp->prev->mode
// 			== TOKEN_Double_Q || tmp->prev->mode == TOKEN_Single_Q || tmp->prev->value[0] 
// 			== ')' || tmp->prev->mode == TOKEN_REDIR_APPEND || tmp->prev->mode 
// 			== TOKEN_REDIR_IN || tmp->prev->mode == TOKEN_REDIR_OUT || tmp->prev->mode == TOKEN_HEREDOC))
// 			return (1);
// 	if (tmp && tmp->prev && tmp->prev->prev)
// 		if (!is_empty(tmp->prev->prev->value) && (tmp->prev->prev->mode == TOKEN_EXPR
// 			|| tmp->prev->prev->mode == TOKEN_Double_Q || tmp->prev->prev->mode
// 			== TOKEN_Single_Q || tmp->prev->prev->value[0] == ')'||  tmp->prev->prev->mode 
// 			== TOKEN_REDIR_IN ||  tmp->prev->prev->mode == TOKEN_REDIR_OUT ||  tmp->prev->prev->mode 
// 			== TOKEN_REDIR_APPEND ||  tmp->prev->prev->mode == TOKEN_HEREDOC))
// 			return (1);
// 	return (0);
// }

static int	check_syntax_4(t_node *tmp)
{
	if (!add_list_redir(tmp))
		return (0);
	if (tmp && tmp->next)
		if (!is_empty(tmp->next->value) && (tmp->next->mode == TOKEN_EXPR || tmp->next->mode
			== TOKEN_Double_Q || tmp->next->mode == TOKEN_Single_Q || tmp->next->value[0] 
			== '(' || tmp->next->mode == TOKEN_REDIR_APPEND || tmp->next->mode
			== TOKEN_REDIR_IN || tmp->next->mode == TOKEN_REDIR_OUT || tmp->next->mode == TOKEN_HEREDOC))
			return (1);
	if (tmp && tmp->next && tmp->next->next)
		if (!is_empty(tmp->next->next->value) && (tmp->next->next->mode == TOKEN_EXPR || tmp->next->next->mode
			== TOKEN_Double_Q || tmp->next->next->mode == TOKEN_Single_Q || tmp->next->next->value[0] == '(' || tmp->next->next->mode 
			== TOKEN_REDIR_IN ||  tmp->next->next->mode == TOKEN_REDIR_OUT ||  tmp->next->next->mode 
			== TOKEN_REDIR_APPEND ||  tmp->next->next->mode == TOKEN_HEREDOC))
			return (1);
	return (printf("ha ana"),0);
}

static int	check_syntax_1(t_node *tmp)
{
	if (!add_list_redir(tmp))
		return (0);
	if (tmp && tmp->next)
		if (!is_empty(tmp->next->value) && (tmp->next->mode == TOKEN_EXPR || tmp->next->mode
			== TOKEN_Double_Q || tmp->next->mode == TOKEN_Single_Q || tmp->next->value[0] == '(' ))
			return (1);
	if (tmp && tmp->next && tmp->next->next)
		if (!is_empty(tmp->next->next->value) && (tmp->next->next->mode == TOKEN_EXPR || tmp->next->next->mode
			== TOKEN_Double_Q || tmp->next->next->mode == TOKEN_Single_Q || tmp->next->next->value[0] == '('))
			return (1);
	return (0);
}

static int	add_args(t_list_arg *list, char *str, int *i)
{
	int			len;
	char		*s;
	t_node_arg	*node;

	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	s = my_malloc(sizeof(char) * (len + 1), 1);
	len = 0;
	while (str && str[len] && str[len] != ' ')
	{
		s[len] = str[len];
		len++;
	}
	s[len] = '\0';
	*i += len;
	node = c_node_arg(s);
	if (!node)
		return (0);
	add_back_arg(list, node);
	return (1);
}

static int	check_syntax_3(t_node *tmp)
{
	char	*str;
	int		i;

	(1 == 1) && (str = NULL, i = -1);
	if (!tmp->value[0])
		return (tmp->val_vide = 1, 1);
	tmp->list_arg = c_list_arg();
	if (!tmp->list_arg)
		return (0);
	str = tmp->value;
	while (str[++i])
		if (str[i] == '$')
			if (!add_args(tmp->list_arg, &str[++i], &i))
				return (0);
	return (1);
}

int	is_empty(char *str)
{
	int i = 0;
	if (str && !str[0])
		return (0);
	while(str[i])
	{
		if (str[i] != ' ')
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
			return (0);
	}
	else if ((node && node->prev)  && (node->prev->mode == TOKEN_EXPR || node->prev->mode 
	== TOKEN_PARENTHESE || node->prev->mode == TOKEN_Single_Q || node->prev->mode ==
	TOKEN_Double_Q || node->prev->mode == TOKEN_REDIR_APPEND || node->prev->mode ==
	TOKEN_REDIR_OUT|| node->prev->mode == TOKEN_REDIR_IN || node->prev->mode == TOKEN_HEREDOC))
		return (0);
	if (node && node->next)
		node = node->next;
	while (node && node->value[0] != ')')
	{
		if (is_empty(node->value))
			return (0);
		i++;
		node = node->next;
	}
	if (i)
		return (1);
	return (0);
}

int	check_apres_parentheses(t_node *node)
{
	if (node && node->next  && node->next->mode == TOKEN_SPACE)
	{
		if (node && node->next && node->next->next && (node->next->next->mode 
		== TOKEN_EXPR || node->next->next->mode == TOKEN_Double_Q || node->next->next->mode 
		== TOKEN_Single_Q || node->next->next->mode == TOKEN_PARENTHESE ))
			return (0);
	}
	else if ((node && node->next)  && (node->next->mode == TOKEN_EXPR || node->next->mode 
	== TOKEN_PARENTHESE || node->next->mode == TOKEN_Single_Q ||  node->next->mode ==
	TOKEN_Double_Q))
		return (0);
	return (1);
}

void	checkSinglQ(t_node *tmp)
{
	if (!tmp-> value[0])
		tmp->val_vide = 1;
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
			else if (tmp->mode == TOKEN_PARENTHESE  && tmp->value[0] == ')' && count_parentheses == 1)
			{
				count_parentheses--;
				if (!check_apres_parentheses(tmp))
					return (0);
			}
			else if (tmp->mode == TOKEN_OR || tmp->mode
				== TOKEN_AND || tmp->mode == TOKEN_PIPE)
			{
				if (!check_syntax_2(tmp) || !check_syntax_4(tmp))
					return (printf("syntax error 2!\n"), 0);
			}
			if (tmp->mode == TOKEN_REDIR_APPEND || tmp->mode
				== TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT
				|| tmp->mode == TOKEN_HEREDOC)
			{
				if (!check_syntax_1(tmp))
					return (printf("syntax error 3!\n"), 0);
			}
			if (tmp->mode == TOKEN_Double_Q)
			{
				if (!check_syntax_3(tmp))
					return (printf("syntax error 4!\n"), 0);
			}
			else if(tmp->mode == TOKEN_Single_Q)
				checkSinglQ(tmp);
			tmp = tmp->next;
		}
	}
	if (count_parentheses != 0)
		return (printf("syntax error 5!\n"), 0);
	return (1);
}
