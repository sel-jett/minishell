/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:03:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 14:23:14 by sel-jett         ###   ########.fr       */
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

int	ft_strncmp_lfassi(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_env_export(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*tmp3;
	char	*key;
	char	*value;
	int		i;

	tmp = env;
	tmp3 = env;
	while (tmp)
	{
	i = 0;
		tmp2 = tmp;
		while (tmp2->next)
		{
			if (tmp2->key && tmp2->next->key && ft_strncmp_lfassi(tmp2->key, tmp2->next->key) > 0)
			{
				key = tmp2->next->key;
				value = tmp2->next->value;
				tmp2->next->key = tmp2->key;
				tmp2->next->value = tmp2->value;
				tmp2->key = key;
				tmp2->value = value;
				tmp = tmp3;
				i = 1;
			}
			tmp2 = tmp2->next;
		}
		if (i == 0)
			tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->key || tmp->value)
			printf("declare -x ");
		if (tmp->key)
		{
			printf("%s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"\n", tmp->value);
			else
				printf("\n");
		}
		else if (tmp->value)
			printf("=\"%s\"\n", tmp->value);
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
		ft_status(0, 1);
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
		if (!tmp[0] && cmd[i][0] != '$')
			tmp = get_key(cmd[i]);
		if (equal_check(cmd[i]) != 0 && equal_check(cmd[i]) != -10)
		{
			ft_list_remove_if(exp, tmp, ft_strncmp);
			ft_list_remove_if(cnev, tmp, ft_strncmp);
		}
		else if (equal_check(cmd[i]) != -10)
		{
			if (!value_key(*exp, tmp))
			{
				ft_lstadd_back(exp, env_new(cmd[i], *exp));
				ft_status(0, 1);
				i++;
				continue ;
			}
		}
		if (get_value(cmd[i]))
		{
			ft_lstadd_back(cnev, env_new(cmd[i], *cnev));
			ft_lstadd_back(exp, env_new(cmd[i], *exp));
			ft_status(0, 1);
		}
		i++;
	}
}
