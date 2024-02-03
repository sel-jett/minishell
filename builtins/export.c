/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:03:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/03 03:10:54 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
			return (0);
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
		printf("=");
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	ft_export(char *cmd, t_env **cnev)
{
	if (!ft_strlen_b(cmd))
	{
		ft_env_export(*cnev);
		return ;
	}
	cmd = ft_strtrim(cmd);
	if (!check_first(cmd))
		return;
	if (equal_check(cmd))
		ft_list_remove_if(cnev, get_key(cmd), ft_strncmp_one);
	if (get_value(cmd))
		ft_lstadd_back(cnev, env_new(cmd, *cnev));
}
