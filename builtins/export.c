/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:03:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/04 18:06:14 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

// static char	*grep_first(char *cmd)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	while (cmd[i] && cmd[i] != '=')
// 		i++;
// 	str = my_malloc(i + 1, 1);
// 	j = -1;
// 	while (++j < i)
// 		str[j] = cmd[i];
// 	str[j] = '\0';
// 	return (str);
// }

// static int	append_check(char *cmd)
// {

// }

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

	i = 0;
	if (!ft_strlen_b(cmd[0]))
	{
		ft_env_export(*exp);
		return ;
	}

	while (cmd[i])
	{
		if (!check_first(cmd[i]))
			return ;
		if (equal_check(cmd[i]) != 0 && equal_check(cmd[i]) != -10)
		{
			ft_list_remove_if(exp, get_key(cmd[i]), ft_strncmp_one);
			ft_list_remove_if(cnev, get_key(cmd[i]), ft_strncmp_one);
		}
		else if (equal_check(cmd[i]) != -10)
		{
			if (!value_key(*exp, get_key(cmd[i])))
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
