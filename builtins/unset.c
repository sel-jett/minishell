/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:27:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/04 18:09:44 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

void	ft_unset(char **cmd, t_env **cnev, t_env **exp)
{
	char	**dptr;
	int		i;

	i = 0;
	while (cmd[i])
	{
		dptr = ft_split(cmd[i], ' ');
		if (dptr[1])
		{
			write(2, "mminishell: unset: `" , 20);
			write(2, cmd[i], ft_strlen_b(cmd[i]));
			write(2, "': not a valid identifier\n", 27);
			// ft_printf("': not a valid identifier\n");
		}
		else
		{
			ft_list_remove_if(cnev, cmd[i], ft_strncmp_one);
			ft_list_remove_if(exp, cmd[i], ft_strncmp_one);
		}
		i++;
	}
}
