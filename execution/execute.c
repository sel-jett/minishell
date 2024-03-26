/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 08:41:03 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**array_31(char **str)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = my_malloc(((ft_strlen_tri(str) + 1) * 8), 1);
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		(1) && (tmp[i] = NULL, j = 0);
		while (str[i][j])
		{
			if (str[i][j] == -31)
			{
				j++;
				continue ;
			}
			tmp[i] = ft_strjoin_char(tmp[i], str[i][j]);
			j++;
		}
		tmp[i] = ft_strjoin_char(tmp[i], '\0');
		i++;
	}
	return (tmp[i] = NULL, tmp);
}

void	c(char **str, int *len)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	while (str[i])
	{
		if (ft_strlen_b(str[i]) != 0 && str[i][ft_strlen_b(str[i]) - 1] && \
			str[i][ft_strlen_b(str[i]) - 1] == -31)
		{
			j = 0;
			s = ft_split(str[i], ' ');
			while (s[j])
			{
				(*len)++;
				j++;
			}
		}
		(*len)++;
		i++;
	}
}

char	**ft_31_s(char **str, int i, int j, int k)
{
	int		len;
	char	**s;
	char	**str_r;

	(1) && (len = 0, c(str, &len), 0);
	str_r = my_malloc((sizeof(char *) * (len + 1)), 1);
	if (!str_r)
		return (0);
	while (str[i])
	{
		if (ft_strlen_b(str[i]) != 0 && str[i][ft_strlen_b(str[i]) - 1] == -31)
		{
			j = 0;
			s = ft_split(str[i], ' ');
			while (s[j])
			{
				str_r[k] = ft_strdup(s[j]);
				(1) && (j++, k++);
			}
		}
		else
			str_r[k++] = strdup(str[i]);
		i++;
	}
	return (str_r[k] = NULL, str_r);
}

void	change(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i][ft_strlen(str[i]) - 1] == -31)
			str[i][strlen(str[i]) - 1] = '\0';
		i++;
	}
}

void	ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp)
{
	char	**cmmd;
	char	**path;
	t_node	*tmp;
	t_split	s;

	(1) && (s.i = 0, s.j = 0, s.k = 0, path = ft_split(get_path(*env), ':'));
	(1) && (tmp = tree->list->top, s.smp = tree->list->top, s.check = 0);
	cmmd = linkedlist_to_arr(tmp, *exp);
	if (!cmmd)
		return ;
	flag_to_expand(s.smp, cmmd, &s.check, exp);
	if (!dup_wild(cmmd, tree->list->top, &s.check))
		return ;
	if (!execute_cmd_child(s.check, &cmmd))
		return ;
	backslach_filler(cmmd);
	if (array_checker(cmmd))
		cmmd = array_structer(cmmd);
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(env_to_arr(*env), \
		array_31(ft_31_s(cmmd, s.i, s.j, s.k)), path);
}
