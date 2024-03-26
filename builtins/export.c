/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:03:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 08:59:31 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	equal_check(char *cmd)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	if (!cmd)
		return (check);
	while (cmd[i])
	{
		if (cmd[i] == '=')
			check = 1;
		if (i > 0 && cmd[i] == '=' && cmd[i - 1] == '+')
			return (-10);
		i++;
	}
	return (check);
}

void	export_value(char **cmd, t_env **cnev, t_env **exp, int i)
{
	if (get_value(cmd[i]))
	{
		ft_lstadd_back(cnev, env_new(cmd[i], *cnev));
		ft_lstadd_back(exp, env_new(cmd[i], *exp));
		ft_status(0, 1);
	}
}

int	value_export(t_env **exp, char **cmd, char *tmp, int *i)
{
	if (!value_key(*exp, tmp))
	{
		ft_lstadd_back(exp, env_new(cmd[*i], *exp));
		ft_status(0, 1);
		(*i)++;
		return (1);
	}
	return (0);
}

void	ft_export_remove(t_env **exp, t_env **cnev, char *tmp)
{
	ft_list_remove_if(exp, tmp, ft_strncmp);
	ft_list_remove_if(cnev, tmp, ft_strncmp);
}

void	ft_export(char **cmd, t_env **cnev, t_env **exp)
{
	int		i;
	char	*tmp;

	(1) && (i = 0, tmp = NULL);
	if (!cmd || !cmd[0])
	{
		(1) && (ft_env_export(*exp, tmp, i), ft_status(0, 1), 0);
		return ;
	}
	while (cmd[i])
	{
		if (!check_first(cmd[i], *exp))
		{
			i++;
			continue ;
		}
		tmp = ft_expand(*exp, get_key(cmd[i]));
		(!tmp && cmd[i][0] != '$') && (tmp = get_key(cmd[i]), 0);
		if (equal_check(cmd[i]) != 0 && equal_check(cmd[i]) != -10)
			ft_export_remove(exp, cnev, tmp);
		else if (equal_check(cmd[i]) != -10)
			if (value_export(exp, cmd, tmp, &i))
				continue ;
		(1) && (export_value(cmd, cnev, exp, i), i++, 0);
	}
}
