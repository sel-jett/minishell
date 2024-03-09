/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/08 15:12:17 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_handler(char **envp, char **cmmd, char **path)
{
	int				i;
	int				check;
	char			*env_var;

	(1) && (check = 0, i = 0, env_var = cmmd[0]);
	while (path[i])
	{
		if (cmmd[0][0] == '/')
			env_var = ft_strjoin("/", cmmd[0]);
		else if (cmmd[0][0] != '.')
		{
			env_var = ft_strjoin("/", cmmd[0]);
			env_var = ft_strjoin(path[i], env_var);
			env_var = ft_strjoin("/", env_var);
		}
		if (!access(env_var, F_OK | X_OK))
			(check = 1) && (ft_execve(env_var, envp, cmmd), 0);
		i++;
	}
	if (!check)
	{
		ft_printf("minishell: ", cmmd[0]);
		ft_printf(": command not found\n", NULL);
	}
}

static char	*get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp_one(env->key, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static bool	is_builtin(char *cmd)
{
	if (!ft_strncmp_one(cmd, "echo") || !ft_strncmp_one(cmd, "cd") || \
		!ft_strncmp_one(cmd, "pwd") || !ft_strncmp_one(cmd, "export") || \
			!ft_strncmp_one(cmd, "unset") || !ft_strncmp_one(cmd, "env"))
		return (1);
	return (0);
}

static void	ft_execute_child(char **envp, char **cmmd, char **path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	else if (!pid)
	{
		ft_handler(envp, cmmd, path);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_status(status, 1);
}

void	ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp)
{
	int				i;
	char			**cmmd;
	char			**path;
	char			**envp;
	t_node			*tmp;

	i = 0;
	tmp = tree->list->top;
	envp = env_to_arr(*env);
	path = ft_split(get_path(*env), ':');
	cmmd = linkedlist_to_arr(tmp);
	while (cmmd[i])
	{
		cmmd[i] = ft_expand(cmmd[i]);
		i++;
	}
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(envp, cmmd, path);
}
