/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:27:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/20 20:19:09 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

int	is_alpha_3(char c)
{
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| c == '_' || (c >= '0' && c <= '9')))
		return (0);
	return (1);
}

int	is_alpha_2(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z') \
			|| c[i] == '_' || (c[i] >= '0' && c[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(char **cmd, t_env **cnev, t_env **exp)
{
	char	**dptr;
	int		i;
	int		j;
	int		check;

	i = 0;
	check = 0;
	while (cmd[i])
	{
		dptr = ft_split(cmd[i], ' ');
		j = 0;
		while (dptr[j])
		{
			if (check == 1 || !is_alpha_2(dptr[j]))
			{
				write(2, "mminishell: unset: `" , 20);
				write(2, dptr[j], ft_strlen_b(dptr[j]));
				write(2, "': not a valid identifier\n", 27);
				check = 1;
				ft_status(1, 1);
			}
			if (!check)
			{
				ft_list_remove_if(cnev, dptr[j], ft_strncmp);
				ft_list_remove_if(exp, dptr[j], ft_strncmp);
				ft_status(0, 1);
			}
			j++;
		}
		i++;
	}
}
