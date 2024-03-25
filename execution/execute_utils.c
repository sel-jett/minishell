/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:03:47 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 18:16:15 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (path && path[i] && cmmd[0][0])
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
		else if (!access(env_var, F_OK))
		{
			ft_printf("minishell: ", cmmd[0]);
			ft_printf(": Permission denied\n", NULL);
			ft_status(126, 1);
			return (NULL);
		}
		i++;
	}
	if (cmmd[0][0] != '/')
	{
		ft_printf("minishell: ", cmmd[0]);
		ft_printf(": command not found\n", NULL);
		ft_status(127, 1);
	}
	return (NULL);
}

void	ft_execute_child(char **envp, char **cmmd, char **path)
{
	pid_t		pid;
	int			status;
	char		*env_var;
	extern int	g_x;

	if (!envp || !envp[0] || !cmmd || !cmmd[0])
		return ;
	// array_checker(cmmd);
	// dprintf(2, "-------------------------------------------\n");
	// ft_print_arr(cmmd);
	// dprintf(2, "-------------------------------------------\n");
	// return;
	env_var = ft_handler(cmmd, path);
	if (env_var || cmmd[0][0] == '/')
	{
		g_x = 1;
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			return ;
		}
		else if (!pid)
		{
			if (cmmd[0][0] == '/')
				(1) && (def_sig(), ft_execve(cmmd[0], envp, cmmd), exit(1), 0);
			else
				(1) && (def_sig(), ft_execve(env_var, envp, cmmd), exit(1), 0);
		}
		waitpid(pid, &status, 0);
		ft_status((status % 255), 1);
	}
}
