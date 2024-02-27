/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:03:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/27 18:25:22 by salah            ###   ########.fr       */
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
	char	**dptr;
	int		i;

	i = 0;
	dptr = ft_split(cmd, ' ');
	while (dptr[i])
	{
		if (!ft_strlen_b(dptr[i]))
		{
			ft_env_export(*cnev);
			return ;
		}
		dptr[i] = ft_strtrim(dptr[i]);
		if (!check_first(dptr[i]))
			return ;
		if (equal_check(dptr[i]))
			ft_list_remove_if(cnev, get_key(dptr[i]), ft_strncmp_one);
		if (get_value(dptr[i]))
			ft_lstadd_back(cnev, env_new(dptr[i], *cnev));
		i++;
	}
}
