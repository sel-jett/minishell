/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plant_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:06:53 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/23 21:37:28 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_two( t_list *list, int *i, int mode)
{
	char	*s;
	int		j;
	t_node	*node;

	(1 == 1) && (j = -1, s = 0, node = 0);
	s = my_malloc(sizeof(char) * 3, 1);
	if (!s)
		return (0);
	while (++j < 2)
		s[j] = list ->str[*i + j];
	s[j] = '\0';
	node = c_node(s, list->tail, mode,list);
	if (!node)
		return (0);
	add_back(list, node);
	*i += 2;
	return (1);
}

int	add_one(t_list *list, int *i, int mode)
{
	char	*s;
	t_node	*node;

	(1 == 1) && (s = 0, node = 0);
	s = my_malloc(sizeof(char) * 2, 1);
	if (!s)
		return (0);
	(1 == 1) && (s[0] = list->str[*i], s[1] = '\0');
	node = c_node(s, list->tail, mode,list);
	if (!node)
		return (0);
	add_back(list, node);
	(*i)++;
	return (1);
}

int	plant_3( t_list *list, int *i)
{
	int	index;
	index = 0;
	if (!list->str)
		return (0);
	if (list->str[*i] == '<')
	{
		if (list->str[*i + 1] && list->str[*i + 1] == '<')
		{
			if (!add_two(list, i, TOKEN_REDIR_IN))
				return (0);
		}
		else
			if (!add_one(list, i, TOKEN_HEREDOC))
				return (0);
	}
	else if (list->str[*i] == '|')
	{
		if (list->str[*i + 1])
		{
			if (list->str[*i + 1] == '|')
			{
				if (!add_two(list, i, TOKEN_OR))
					return (0);
				index = 1;
			}
		}
		if (index == 0)
			if (!add_one(list, i, TOKEN_PIPE))
				return (0);
	}
	else if (list->str[*i] == '>')
	{
		if (list->str[*i + 1] && list->str[*i + 1] == '>')
		{
			if (!add_two(list, i, TOKEN_REDIR_APPEND))
				return (0);
		}
		else
			if (!add_one(list, i, TOKEN_REDIR_OUT))
				return (0);
	}
	else if (list->str[*i] == '&')
	{
		if (list->str[*i + 1] && list->str[*i + 1] == '&')
		{
			if (!add_two(list, i, TOKEN_AND))
				return (0);
		}
		else
			return (0);
	}
	return (1);
}
