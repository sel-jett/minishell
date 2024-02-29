/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/29 18:40:04 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_handler(char *env_var, char **env, char **cmmd)
{
	if (!access(env_var, F_OK))
	{
		if (!access(env_var, X_OK))
		{
			// fprintf(stderr, ">>>>>>>> envvar: %s, cmmd: %s, env: %s\n", env_var, cmmd[0], env[0]);
			if (execve(env_var, cmmd, env) == -1)
				write(2, "error execve\n", 16);
		}
		else
			write(2, "error execve\n", 16);
	}
}

char	**env_to_arr(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	tmp = env;
	while (tmp)
	{
		// exit(1);
		arr[i] = ft_strjoin(tmp->key, "=");
		arr[i] = ft_strjoin(arr[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
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

void	ft_print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

int	liked_size(t_node *tree)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = tree;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);

}

char	**linkedlist_to_arr(t_node *tree)
{
	char	**arr;
	int		i;
	t_node	*tree_tmp;
	t_node	*tmp;

	tree_tmp = tree;
	tmp = tree;
	i = liked_size(tree_tmp);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	while (tmp)
	{
		arr[i] = ft_strdup(tmp->value);
		// puts(tmp->value);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

static bool	is_builtin(char *cmd)
{
	if (!ft_strncmp_one(cmd, "echo") || !ft_strncmp_one(cmd, "cd") || \
		!ft_strncmp_one(cmd, "pwd") || !ft_strncmp_one(cmd, "export") || \
			!ft_strncmp_one(cmd, "unset") || !ft_strncmp_one(cmd, "env"))
		return (1);
	return (0);

}

void	ft_execute_cmd(t_node_arbre *tree, t_env **env)
{
	int				i;
	char			*env_var;
	char			**cmmd;
	char			**path;
	char			**envp;
	t_node			*tmp;
	pid_t			pid;
	int				status;

	i = 0;
	tmp = tree->list->top;
	envp = env_to_arr(*env);
	path = ft_split(get_path(*env), ':');
	cmmd = linkedlist_to_arr(tmp);
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env);
		return ;
	}
	env_var = cmmd[0];
	i = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (!pid)
	{
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
			ft_handler(env_var, envp, cmmd);
			i++;
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_status(status, 1);
}
