/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:33:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 19:54:27 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execve(char *env_var, char **env, char **cmmd)
{
	if (execve(env_var, cmmd, env))
	{
		ft_printf("minishell: ", cmmd[0]);
		ft_printf(": ", NULL);
		perror("");
		exit(126);
	}
}

// char	*array_joner()
// {}

char	**arr_filler(t_node	*tmp, char **arr, int i)
{
	int		check;

	check = 0;
	if (tmp->value && ft_strcmp(tmp->value, "export"))
		check = 1;
	while (tmp)
	{
		if (tmp->value && !(tmp->value)[0] && i > 0 && tmp->flag_space == 0)
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
		if (tmp->value && !tmp->flag_space)
		{
			arr[i] = ft_strjoin(arr[i], tmp->value);
			if (!arr[i])
				return (NULL);
		}
		else if (tmp->value && tmp->flag_space == 1)
		{
			if (arr[i])
				(1) && (i++, arr[i] = ft_strjoin(arr[i], tmp->value), 0);
			else
				arr[i] = ft_strjoin(arr[i], tmp->value);
			if (!arr[i])
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (i++, arr[i] = NULL, arr);
}
