/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:03:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/18 23:28:16 by sel-jett         ###   ########.fr       */
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

void	ft_env_export(t_env *tmp)
{
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"\n", tmp->value);
		else
			printf("\n");
		tmp = tmp->next;
	}
}

void	ft_export(char **cmd, t_env **cnev, t_env **exp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_strlen_b(cmd[0]))
	{
		ft_env_export(*exp);
		return ;
	}

	while (cmd[i])
	{
		tmp = ft_expand(*exp, get_key(cmd[i]));
		if (!tmp[0] && cmd[i][0] != '$')
			tmp = get_key(cmd[i]);
		if (!check_first(cmd[i], *exp))
			return ;
		if (equal_check(cmd[i]) != 0 && equal_check(cmd[i]) != -10)
		{
			ft_list_remove_if(exp, tmp, ft_strncmp_one);
			ft_list_remove_if(cnev, tmp, ft_strncmp_one);
		}
		else if (equal_check(cmd[i]) != -10)
		{
			if (!value_key(*exp, tmp))
			{
				ft_lstadd_back(exp, env_new(cmd[i], *exp));
				i++;
				continue;
			}
		}
		if (get_value(cmd[i]))
		{
			ft_lstadd_back(cnev, env_new(cmd[i], *cnev));
			ft_lstadd_back(exp, env_new(cmd[i], *exp));
		}
		i++;
	}
	ft_sort_list(exp);
}
