/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:03:47 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 01:51:23 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*cmd_with_path(char **cmmd, char **path, char *env_var, int *i)
{
	if (cmmd[0][0] == '/')
	{
		env_var = ft_strjoin("/", cmmd[0]);
		if (!env_var)
			return (NULL);
	}
	else if (cmmd[0][0] != '.')
		if (!ft_str_joiner(&env_var, path, cmmd, i))
			return (NULL);
	return (env_var);
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
		env_var = cmd_with_path(cmmd, path, env_var, &i);
		if (!access(env_var, F_OK | X_OK))
			return (env_var);
		else if (!access(env_var, F_OK))
		{
			(1) && (ft_printf("minishell: ", cmmd[0]), ft_status(126, 1));
			ft_printf(": Permission denied\n", NULL);
			return (NULL);
		}
		i++;
	}
	if (cmmd[0][0] != '/')
	{
		(1) && (ft_printf("minishell: ", cmmd[0]), ft_status(127, 1));
		ft_printf(": command not found\n", NULL);
	}
	return (NULL);
}

void	ft_execute_grand_child(char **envp, char **cmmd, char *env_var)
{
	if (cmmd[0][0] == '/')
		(1) && (def_sig(), ft_execve(cmmd[0], envp, cmmd), exit(1), 0);
	else
		(1) && (def_sig(), ft_execve(env_var, envp, cmmd), exit(1), 0);
}

void	ft_execute_child(char **envp, char **cmmd, char **path)
{
	pid_t		pid;
	int			status;
	char		*env_var;
	extern int	g_x;

	if (!envp || !envp[0] || !cmmd || !cmmd[0])
		return ;
	env_var = ft_handler(cmmd, path);
	if (env_var || cmmd[0][0] == '/' || cmmd[0][0] == '.')
	{
		g_x = 1;
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			return ;
		}
		else if (!pid)
			ft_execute_grand_child(envp, cmmd, env_var);
		waitpid(pid, &status, 0);
		ft_status((status % 255), 1);
	}
}
