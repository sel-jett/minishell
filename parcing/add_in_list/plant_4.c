/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plant_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:28:51 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 09:32:24 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	oxe1_plant3(char c, int *i, t_list *list)
{
	if (c && c == '<')
	{
		if (!add_two(list, i, TOKEN_HEREDOC))
			return (0);
	}
	else
		if (!add_one(list, i, TOKEN_REDIR_IN))
			return (0);
	return (1);
}

static int	oxe2_plant3(char c, int *i, t_list *list)
{
	int	index;

	index = 0;
	if (c)
	{
		if (c == '|')
		{
			if (!add_two(list, i, TOKEN_OR))
				return (0);
			index = 1;
		}
	}
	if (index == 0)
		if (!add_one(list, i, TOKEN_PIPE))
			return (0);
	return (1);
}

static int	oxe3_plant3(char c, int *i, t_list *list)
{
	if (c && c == '>')
	{
		if (!add_two(list, i, TOKEN_REDIR_APPEND))
			return (0);
	}
	else
		if (!add_one(list, i, TOKEN_REDIR_OUT))
			return (0);
	return (1);
}

static int	oxe4_plant3(char c, int *i, t_list *list)
{
	if (c && c == '&')
	{
		if (!add_two(list, i, TOKEN_AND))
			return (0);
	}
	else
		return (affichage(-2), ft_status(258, 1), 0);
	return (1);
}

int	plant_3( t_list *list, int *i)
{
	if (!list->str)
		return (0);
	if (list->str[*i] == '<')
	{
		if (!oxe1_plant3(list->str[*i + 1], i, list))
			return (0);
	}
	else if (list->str[*i] == '|')
	{
		if (!oxe2_plant3(list->str[*i + 1], i, list))
			return (0);
	}
	else if (list->str[*i] == '>')
	{
		if (!oxe3_plant3(list->str[*i + 1], i, list))
			return (0);
	}
	else if (list->str[*i] == '&')
		if (!oxe4_plant3(list->str[*i + 1], i, list))
			return (0);
	return (1);
}
