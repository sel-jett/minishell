/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 07:05:43 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp_one(env->key, "PATH"))
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

char	*ft_str_joiner(char **env_var, char **path, char **cmmd, int *i)
{
	*env_var = ft_strjoin("/", cmmd[0]);
	if (!*env_var)
		return (NULL);
	*env_var = ft_strjoin(path[*i], *env_var);
	if (!*env_var)
		return (NULL);
	*env_var = ft_strjoin("/", *env_var);
	if (!*env_var)
		return (NULL);
	return (*env_var);
}

char	*ft_handler(char **cmmd, char **path)
{
	int				i;
	char			*env_var;

	if (!cmmd || !cmmd[0])
		return (NULL);
	(1) && (i = 0, env_var = cmmd[0]);
	while (path[i] && cmmd[0][0])
	{
		if (cmmd[0][0] == '/')
		{
			env_var = ft_strjoin("/", cmmd[0]);
			if (!env_var)
				return (NULL);
		}
		else if (cmmd[0][0] != '.')
			if (!ft_str_joiner(&env_var, path, cmmd, &i))
				return (NULL);
		if (!access(env_var, F_OK | X_OK))
			return (env_var);
		i++;
	}
	ft_printf("minishell: ", cmmd[0]);
	ft_printf(": command not found\n", NULL);
	ft_status(127, 1);
	return (NULL);
}

void	ft_execute_child(char **envp, char **cmmd, char **path)
{
	pid_t		pid;
	int			status;
	char		*env_var;
	extern int	x;

	if (!path || !path[0])
		return ;
	env_var = ft_handler(cmmd, path);
	if (env_var)
	{
		x = 1;
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			return ;
		}
		else if (!pid)
		{
			(1) && (def_sig(), ft_execve(env_var, envp, cmmd), 0);
			exit(0);
		}
		waitpid(pid, &status, 0);
		ft_status((status % 255), 1);
	}
}

char	**checkerr(char *str, int *len)
{
	char	**str_r;
	int		i;

	i = 0;
	str_r = ft_split(str, ' ');
	if (!str_r)
		return (NULL);
	while (str_r[i])
		i++;
	(*len) += i;
	return (str_r);
}

char	**ft_spliter(char **str, char	**str_r)
{
	int		i;
	int		j;
	int		len;
	char	**s;

	i = 0;
	len = 0;
	while (str[i])
	{
		j = 0;
		s = ft_split(str[i], ' ');
		if (!s)
			return (NULL);
		while (s[j])
		{
			str_r[len] = s[j];
			len++;
			j++;
		}
		i++;
	}
	str_r[len] = NULL;
	return (str_r);
}

char	**array_dupper(char **str)
{
	char	**str_r;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		checkerr(str[i], &len);
		if (!str[i])
			return (NULL);
		i++;
	}
	str_r = malloc(sizeof(char *) * (len + 1));
	if (!str_r)
		return (NULL);
	return (ft_spliter(str, str_r));
}

int	first_key_checker(char *cmmd)
{
	int	i;

	i = 0;
	if (cmmd[i] && cmmd[i] == '$' && cmmd[i + 1] && !is_alpha_3(cmmd[i + 1]) \
		&& cmmd[i + 1] != '?')
		return (1);
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
		wild = ft_execute_wild(cmmd[i]);
		if (wild && smp->flag_wilc == 1)
		{
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

void	ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp)
{
	int				i;
	char			**cmmd;
	char			**path;
	char			*backup;
	char			**envp;
	t_node			*tmp;
	t_node			*smp;
	int				check;

	i = 0;
	check = 0;
	tmp = tree->list->top;
	smp = tree->list->top;
	envp = env_to_arr(*env);
	if (!envp)
		return ;
	path = ft_split(get_path(*env), ':');
	if (!path)
		return ;
	cmmd = linkedlist_to_arr(tmp);
	if (!cmmd)
		return ;
	while (cmmd[i])
	{
		if (smp->flag_expend == 1 && !first_key_checker(cmmd[i]))
		{
			backup = ft_expand(*exp, cmmd[i]);
			if (!backup)
				cmmd[i] = "";
			else
				cmmd[i] = backup;
			if (smp->flag_quote != 1 && smp->flag_quote != 2)
				check = 1;
			if (!cmmd[i])
				break ;
		}
		else if (smp->flag_expend == 2 && !first_key_checker(cmmd[i]))
		{
			backup = ft_expand(*exp, cmmd[i]);
			if (!backup)
				cmmd[i] = "";
			else
				cmmd[i] = backup;
			if (smp->flag_quote != 1 && smp->flag_quote != 2)
				check = 1;
			if (!cmmd[i])
				break ;
		}
		i++;
		smp = smp->next;
	}
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
