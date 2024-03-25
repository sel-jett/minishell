/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:33:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 21:37:37 by sel-jett         ###   ########.fr       */
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

char	*arr_value(t_node *tmp, char **str, int *i)
{
	if (*str)
		(1) && ((*i)++, str[*i] = ft_strjoin(str[*i], tmp->value), 0);
	else
		str[*i] = ft_strjoin(str[*i], tmp->value);
	if (!str[*i])
		return (NULL);
	return (str[*i]);
}

char	**arr_filler(t_node	*tmp, char **a, int i)
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
				(1) && (a[i] = ft_strjoin(a[i], "\\"), tmp->flag_space = 1);
		}
		if (tmp->value && !tmp->flag_space)
			a[i] = ft_strjoin(a[i], tmp->value);
		else if (tmp->value && tmp->flag_space == 1)
			a[i] = arr_value(tmp, a, &i);
		if (!a[i])
			return (NULL);
		tmp = tmp->next;
	}
	return (i++, a[i] = NULL, a);
}
