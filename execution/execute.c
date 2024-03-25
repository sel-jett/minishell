/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 20:07:10 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_bi(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_func_string(char **str, int i)
{
	char	**tmp;
	int		len;
	int		j;

	len = ft_strlen_bi(str);
	tmp = my_malloc((len * 8), 1);
	if (!tmp)
		return (NULL);
	len = 0;
	j = 0;
	while (str[len])
	{
		if (i == len)
		{
			len += 1;
			continue ;
		}
		tmp[j] = str[len];
		len++;
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char	**array_structer(char **str)
{
	int	tab[2];

	(1) && (tab[0] = 0, tab[1] = 0);
	while (str && str[tab[0]] && str[tab[0]][0])
	{
		while (str[tab[0]][tab[1]])
		{
			if (str[tab[0]][0] == '\\')
			{
				if (str[tab[0] + 1])
				{
					(1) && (str = ft_func_string(str, tab[0]), tab[0] = 0);
					continue ;
				}
				else
				{
					str[tab[0]] = NULL;
					break ;
				}
			}
			tab[1]++;
		}
		(1) && (tab[1] = 0, tab[0]++);
	}
	return (str = joyner(str), str);
}

int	array_checker(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\v' || str[i][j] == '\\' || str[i][j] == -32)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp)
{
	char			**cmmd;
	char			**path;
	t_node			*tmp;
	t_node			*smp;
	int				check;

	(1) && (tmp = tree->list->top, smp = tree->list->top, check = 0);
	path = ft_split(get_path(*env), ':');
	cmmd = linkedlist_to_arr(tmp);
	if (!cmmd)
		return ;
	flag_to_expand(smp, cmmd, &check, exp);
	if (!dup_wild(cmmd, tree->list->top, &check))
		return ;
	if (!execute_cmd_child(check, &cmmd))
		return ;
	backslach_filler(cmmd);
	if (array_checker(cmmd))
		cmmd = array_structer(cmmd);
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(env_to_arr(*env), cmmd, path);
}
