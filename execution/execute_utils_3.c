/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:23:45 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 17:37:38 by sel-jett         ###   ########.fr       */
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

char	*get_path(t_env *env)
{
	while (env)
	{
		if (env->key && !ft_strncmp_one(env->key, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

bool	is_builtin(char *cmd)
{
	if (!ft_strncmp_one(cmd, "echo") || !ft_strncmp_one(cmd, "cd") || \
		!ft_strncmp_one(cmd, "pwd") || !ft_strncmp_one(cmd, "export") || \
			!ft_strncmp_one(cmd, "unset") || !ft_strncmp_one(cmd, "env") || \
				!ft_strncmp_one(cmd, "exit"))
		return (1);
	return (0);
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
			(1) && (cmmd[i][0] = '\v', cmmd[i][1] = '\0');
			i++;
			continue ;
		}
		if ((smp->flag_expend == 1 && !first_key_checker(cmmd[i])) || \
				(smp->flag_expend == 2 && !first_key_checker(cmmd[i])))
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
	}
	return (1);
}
