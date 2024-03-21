/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plants.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:34:19 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 01:22:41 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	plants(t_list *list, int *i)
{
	if (list->str[*i] == '\t' || list->str[*i] == '\v'
		|| list->str[*i] == '\f' || list->str[*i] == '\n'
		|| list->str[*i] == '\r')
		list->str[*i] = ' ';
	else if ((list->str[*i] == '"' || list->str[*i] == '\''))
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
