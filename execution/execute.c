/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 08:50:48 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	first_key_checker(char *cmmd)
{
	int	i;

	i = 0;
	if (cmmd[i] && cmmd[i] == '$' && cmmd[i + 1] && !is_alpha_3(cmmd[i + 1]) \
		&& cmmd[i + 1] != '?')
		return (1);
	return (0);
}

int	contain_wild(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

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

void	ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp)
{
	char			**cmmd;
	char			**path;
	char			**envp;
	t_node			*tmp;
	t_node			*smp;
	int				check;

	(1) && (tmp = tree->list->top, smp = tree->list->top, check = 0);
	envp = env_to_arr(*env);
	if (!envp)
		return ;
	path = ft_split(get_path(*env), ':');
	if (!path)
		return ;
	cmmd = linkedlist_to_arr(tmp);
	if (!cmmd)
		return ;
	flag_to_expand(smp, cmmd, &check, exp);
	if (!dup_wild(cmmd, tree->list->top, &check))
		return ;
	if (check)
	{
		cmmd = array_dupper(cmmd);
		if (!cmmd)
			return ;
		cmmd = joyner(cmmd);
		if (!cmmd)
			return ;
	}
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(envp, cmmd, path);
}
