/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 14:48:34 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dup_wild(char **cmmd, t_node *smp, int *check)
{
	int		i;
	char	*wild;

	i = 0;
	wild = NULL;
	while (cmmd[i])
	{
		if (contain_wild(cmmd[i]))
		{
			wild = ft_execute_wild(cmmd[i]);
			cmmd[i] = ft_strdup(wild);
			if (!cmmd[i])
				return (NULL);
			*check = 1;
		}
		smp = smp->next;
		i++;
	}
	return (cmmd[0]);
}

void	flag_to_expand(t_node *smp, char **cmmd, int *check, t_env **exp)
{
	char	*backup;

	int		i;

	i = 0;
	while (cmmd[i])
	{
		if (!cmmd[i][0])
		{
			cmmd[i] = my_malloc(2, 1);
			cmmd[i][0] = '\v';
			cmmd[i][1] = '\0';
			i++;
			continue ;
		}
		if (smp->flag_expend == 1 && !first_key_checker(cmmd[i]))
		{
			backup = ft_expand(*exp, cmmd[i]);
			(!backup) && (cmmd[i] = "");
			(backup) && (cmmd[i] = backup);
			(smp->flag_quote != 1 && smp->flag_quote != 2) && (*check = 1);
		}
		else if (smp->flag_expend == 2 && !first_key_checker(cmmd[i]))
		{
			backup = ft_expand(*exp, cmmd[i]);
			(!backup) && (cmmd[i] = "");
			(backup) && (cmmd[i] = backup);
			(smp->flag_quote != 1 && smp->flag_quote != 2) && (*check = 1);
		}
		i++;
		smp = smp->next;
	}
}

int	execute_cmd_child(int check, char ***cmmd)
{
	if (check)
	{
		*cmmd = array_dupper(*cmmd);
		if (!*cmmd)
			return (0);
		*cmmd = joyner(*cmmd);
		if (!*cmmd)
			return (0);
		// ft_print_arr(*cmmd);
		// exit(0);
	}
	return (1);
}

void array_structer_2(char **str)
{
	int i;

	i = 0;
	while (str && str[i] && str[i][0])
	{
		int n = (ft_strlen(str[i]) - 1);
		if (str[i] && str[i][n] && str[i][n] == '\\')
			str[i][n] = '\0';
		i++;
	}
}

char	*ft_func(char *str)
{
	int	len;
	int	j;

	len = ft_strlen_b(str);
	char	*tmp = my_malloc(len - 1, 1);
	if (!tmp)
		return (NULL);
	len = 0;
	j = 0;
	while (str[len])
	{
		if (str[len] == '\\')
			len += 2;
		tmp[j] = str[len];
		len++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int ft_strlen_bi(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_func_string(char **str, int i)
{
	int	len;
	int	j;

	len = ft_strlen_bi(str);
	char	**tmp = my_malloc((len * 8), 1);
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
	int	i;
	int	j;

	i = 0;
	while (str && str[i] && str[i][0])
	{
		j = 0;
		while (str[i][j])
		{
			 if (str[i][0] == '\\')
			{
				if (str[i + 1])
				{
					str = ft_func_string(str, i);
					i = 0;
					continue ;
				}
				else
				{
					str[i] = NULL;
					break ;
				}
			}
			j++;
		}
		i++;
	}
	// exit(0);
	str = joyner(str);
	// ft_print_arr(str);
	return (str);
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
	// if (!path)
	// 	return ;
	cmmd = linkedlist_to_arr(tmp);
	if (!cmmd)
		return ;
	flag_to_expand(smp, cmmd, &check, exp);
	if (!dup_wild(cmmd, tree->list->top, &check))
		return ;
	if (!execute_cmd_child(check, &cmmd))
		return ;
	backslach_filler(cmmd);
	cmmd = array_structer(cmmd);
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(env_to_arr(*env), cmmd, path);
}
