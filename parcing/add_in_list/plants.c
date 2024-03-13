/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plants.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:34:19 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/13 03:30:45 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	plants(t_list *list, int *i)
{
	if (list->str[*i] == '\t' || list->str[*i] == '\v' || list->str[*i] == '\f' || list->str[*i] == '\n' || list->str[*i] == '\r')
		(*i)++;
	if ((list->str[*i] == '"' || list->str[*i] == '\''))
	{		
		if (!plant_1(list, i))
			return (printf("ERROR2\n"), 0);
	}
	else if (list->str[*i] == '(' || list->str[*i] == ')')
	{
		if (!add_one(list, i, TOKEN_PARENTHESE))
			return (printf("ERROR3\n"), 0);
	}
	else if (list->str[*i] == ' ' )
	{
		if (!spaces(list, i))
			return (printf("ERROR4\n"), 0);
	}
	else	if (check(list->str[*i]))
	{
		if (!plant_2(list, i))
			return (printf("ERROR5\n"), 0);
	}
	else if (!check(list->str[*i]))
		if (!plant_3(list, i))
			return (printf("ERROR6\n"), 0);
	return (1);
}
