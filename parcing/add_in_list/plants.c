/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plants.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:34:19 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 08:09:01 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	oxe_1(char c)
{
	if (c == '\t' || c == '\v'
		|| c == '\f' || c == '\n'
		|| c == '\r')
		return (1);
	return (0);
}

int	plants(t_list *list, int *i)
{
	(oxe_1(list->str[*i])) && (list->str[*i] = ' ');
	if ((list->str[*i] == '"' || list->str[*i] == '\''))
	{
		if (!plant_1(list, i))
			return (ft_status(258, 1), affichage(-1), 0);
	}
	else if (list->str[*i] == '(' || list->str[*i] == ')')
	{
		if (!add_one(list, i, TOKEN_PARENTHESE))
			return (0);
	}
	else if (list->str[*i] == ' ')
	{
		if (!spaces(list, i))
			return (0);
	}
	else if (check(list->str[*i]))
	{
		if (!plant_2(list, i))
			return (0);
	}
	else if (!check(list->str[*i]))
		if (!plant_3(list, i))
			return (0);
	return (1);
}
