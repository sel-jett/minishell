/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:33:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/23 23:30:05 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execve(char *env_var, char **env, char **cmmd)
{
	if (execve(env_var, cmmd, env) == -1)
	{
		ft_printf("minishell: ", cmmd[0]);
		ft_printf(": ", NULL);
		perror("");
		exit(127);
	}
}

char	**arr_filler(t_node	*tmp, char **arr, int i)
{
	int		check;

	check = 0;
	if (ft_strcmp(tmp->value, "export"))
		check = 1;
	while (tmp)
	{
		if (!(tmp->value)[0] && i > 0 && tmp->flag_space == 0)
		{
			tmp = tmp->next;
			if (!tmp)
				break ;
			if (check == 0)
			{
				arr[i] = ft_strjoin(arr[i], "\\");
				tmp->flag_space = 1;
			}
		}
		if (!tmp->flag_space)
		{
			arr[i] = ft_strjoin(arr[i], tmp->value);
			if (!arr[i])
				return (NULL);
		}
		else if (tmp->flag_space == 1)
		{
			(1) && (i++, arr[i] = ft_strjoin(arr[i], tmp->value), 0);
			if (!arr[i])
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (++i, arr[i] = NULL, arr);
}
