/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plants.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:34:19 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/17 03:47:12 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int plants_0 (t_list *list, int *i, char *str)
{
    if (check(str[0]))
	{
		if (!plant_2(&str[0], list, i))
		{
			printf("ERROR5\n");
			return (0);
		}
	}
	else if (!check(str[0]))
	{
		if (!plant_3(&str[0], list, i))
		{
			printf("ERROR6\n");
			return (0);
		}
	}
    return (1);
}

int plants(t_list *list, int *i, char *str)
{
        if (str[0] == '(' || str[0] == ')')
		{
			if (!add_one(&str[0], list, i, TOKEN_PARENTHESE)){
				printf("ERROR2\n");
				return (0);
			}
		}
		else if (str[0] == ' ')
		{
			if (!spaces(&str[0], list, i))
			{
				printf("ERROR3\n");
				return (0);
			}
		}
		else if ((str[0] == '"' || str[0] == '\''))
		{
			if (!plant_1(&str[0], list, i))
			{
				printf("ERROR4\n");
				return (0);
			}
		}
		else
            if (!plants_0(list, i, str))
                return (0);
        return (1);
}