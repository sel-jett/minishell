/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:33:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 04:35:41 by amel-has         ###   ########.fr       */
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
	if (*str && str[*i] && tmp && tmp->flag_space == 0)
		(1) && (str[*i] = ft_strjoin(str[*i], tmp->value));
	else if (*str)
	{
		str[*i] = ft_strjoin_char(str[*i], -32);
		(1) && ((*i)++, str[*i] = ft_strjoin(str[*i], tmp->value), 0);
	}
	else
		str[*i] = ft_strjoin(str[*i], tmp->value);
	if (!str[*i])
		return (NULL);
	return (str[*i]);
}

char	**arr_filler(t_node	*tmp, char **a, int i, t_env *exp)
{
	int		check;
	t_node	*tmp2;

	check = 0;
	tmp2 = tmp;
	if (tmp->value && ft_strcmp(tmp->value, "export"))
		check = 1;
	(void)exp;
	while (tmp)
	{
		if (tmp->value && !(tmp->value)[0] && tmp->flag_space == 0 && !a[i])
			a[i] = ft_strdup("");
		else if (tmp->value && !(tmp->value)[0] && tmp->flag_space == 1)
		{
			if (a[i])
				i++;
			a[i] = ft_strdup("");
		}
		else if (tmp->value && (tmp->value)[0] && tmp->flag_space == 1 && tmp->flag_expend == 1)
		{
			i++;
			a[i] = ft_strjoin(a[i], ft_expand(exp, tmp->value));
		}
		else if (tmp->value && (tmp->value)[0] && tmp->flag_space == 1 &&  tmp->flag_expend == 2 )
		{
			i++;
			a[i] = ft_strjoin(a[i], ft_expand(exp, tmp->value));
			a[i] = ft_strjoin_char(a[i], -31);
		}
		else if (tmp->value && (tmp->value)[0] && tmp->flag_space == 0 && tmp->flag_expend == 2)
		{
			a[i] = ft_strjoin(a[i], ft_expand(exp, tmp->value));
			a[i] = ft_strjoin_char(a[i], -31);
		}
		else if (tmp->value && (tmp->value)[0] && tmp->flag_space == 0 && tmp->flag_expend == 1)
		{
			a[i] = ft_strjoin(a[i], ft_expand(exp, tmp->value));
		}
		else if (tmp->value && (tmp->value)[0] && tmp->flag_space == 0)
			a[i] = ft_strjoin(a[i], tmp->value);
		else if (tmp->value && (tmp->value)[0] && tmp->flag_space == 1)
		{
			i++;
			a[i] = ft_strjoin(a[i], tmp->value);
		}
		tmp = tmp->next;
	}
	return (i++, a[i] = NULL, a);
}
