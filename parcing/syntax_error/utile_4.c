/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:32:37 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/06 01:40:25 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax_2(t_node *tmp)//or and
{
	if (tmp && tmp->prev)
		if (!is_empty(tmp->prev->value) && (tmp->prev->mode == TOKEN_EXPR || tmp->prev->mode
			== TOKEN_Double_Q || tmp->prev->mode == TOKEN_Single_Q || tmp->prev->value[0] == ')'))
			return (1);
	if (tmp && tmp->prev && is_empty(tmp->prev->value) && tmp->prev->prev)
		if (!is_empty(tmp->prev->prev->value) && (tmp->prev->prev->mode == TOKEN_EXPR
			|| tmp->prev->prev->mode == TOKEN_Double_Q || tmp->prev->prev->mode
			== TOKEN_Single_Q || tmp->prev->prev->value[0] == ')'))
			return (1);
	return (0);
}

int	check_syntax_4(t_node *tmp)
{
	if (!add_list_redir(tmp))
		return (0);
	if (tmp && tmp->next)
		if (!is_empty(tmp->next->value) && (tmp->next->mode == TOKEN_EXPR || tmp->next->mode
			== TOKEN_Double_Q || tmp->next->mode == TOKEN_Single_Q || tmp->next->value[0]
			== '(' || tmp->next->mode == TOKEN_REDIR_APPEND || tmp->next->mode
			== TOKEN_REDIR_IN || tmp->next->mode == TOKEN_REDIR_OUT || tmp->next->mode == TOKEN_HEREDOC))
			return (1);
	if (tmp && tmp->next && is_empty(tmp->next->value) && tmp->next->next)
		if (!is_empty(tmp->next->next->value) && (tmp->next->next->mode ==
			TOKEN_EXPR || tmp->next->next->mode == TOKEN_Double_Q || tmp->next->next->mode
			== TOKEN_Single_Q || tmp->next->next->value[0] == '(' || tmp->next->next->mode
			== TOKEN_REDIR_IN ||  tmp->next->next->mode == TOKEN_REDIR_OUT ||  tmp->next->next->mode
			== TOKEN_REDIR_APPEND ||  tmp->next->next->mode == TOKEN_HEREDOC))
			return (1);
	return (printf("ha ana"), 0);
}

int	check_syntax_1(t_node *tmp)//redir
{
	if (!add_list_redir(tmp))
		return (0);
	if (tmp && tmp->next)
		if (!is_empty(tmp->next->value) && (tmp->next->mode == TOKEN_EXPR || tmp->next->mode
			== TOKEN_Double_Q || tmp->next->mode == TOKEN_Single_Q || tmp->next->value[0] == '(' ))
			return (1);
	if (tmp && tmp->next && is_empty(tmp->next->value) && tmp->next->next)
		if (!is_empty(tmp->next->next->value) && (tmp->next->next->mode == TOKEN_EXPR || tmp->next->next->mode
			== TOKEN_Double_Q || tmp->next->next->mode == TOKEN_Single_Q || tmp->next->next->value[0] == '('))
			return (1);
	return (0);
}

int	add_args(t_nlist *list, char *str, int *i)
{
	int			len;
	char		*s;
	t_nnode		*node;

	len = 0;
	if(!str)
		return (0);
	while (str[len] && str[len] != ' ' && str[len] != '$')
		len++;
	s = my_malloc(sizeof(char) * (len + 1), 1);
	if (!s)
		return (0);
	len = 0;
	while (str && str[len] && str[len] != ' ' && str[len] != '$')
	{
		s[len] = str[len];
		len++;
	}
	s[len] = '\0';
	*i += len;
	node = c_nnode(s);
	if (!node)
		return (0);
	add_nback(list, node);
	return (1);
}

int	check_syntax_3(t_node *tmp)
{
	char	*str;
	int		i;


	str = tmp->value;
	(1) && ((str = NULL) && (i = -1));
	if (!tmp->value[0])
		return (tmp->val_vide = 1, 1);
	tmp->list_arg = c_nlist();
	if (!tmp->list_arg)
		return (0);
	while (str && str[++i])
		while (str  && str[i] && str[i] == '$')
		{
			i++;
			if (str && str[i] && !add_args(tmp->list_arg, &str[i], &i))
				return (0);
		}
	return (1);
}
