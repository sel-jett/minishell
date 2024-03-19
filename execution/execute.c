/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:39 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/19 07:36:48 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_handler(char **envp, char **cmmd, char **path)
// {
// 	int				i;
// 	int				check;
// 	char			*env_var;

// 	if (!cmmd || !cmmd[0] || !cmmd[0][0])
// 		return ;
// 	if (!ft_strncmp(cmmd[0], "."))
// 	{
// 		ft_printf(".: not enough arguments\n", NULL);
// 		return ;
// 	}
// 	(1) && (check = 0, i = 0, env_var = cmmd[0]);
// 	// ft_print_arr(cmmd);
// 	// exit(0);
// 	// puts("///////////////////////////////path///////////////////////////////\n\n\n");
// 	// ft_print_arr(path);
// 	// puts("///////////////////////////////envp///////////////////////////////\n\n\n");
// 	// ft_print_arr(envp);
// 	// exit(0);
// 	while (path[i])
// 	{
// 		if (cmmd[0][0] == '/')
// 			env_var = ft_strjoin("/", cmmd[0]);
// 		else if (cmmd[0][0] != '.')
// 		{
// 			env_var = ft_strjoin("/", cmmd[0]);
// 			env_var = ft_strjoin(path[i], env_var);
// 			env_var = ft_strjoin("/", env_var);
// 		}
// 		if (!access(env_var, F_OK | X_OK))
// 			(check = 1) && (ft_execve(env_var, envp, cmmd), 0);
// 		i++;
// 	}
// 	if (!check)
// 	{
// 		ft_printf("minishell: ", cmmd[0]);
// 		ft_printf(": command not found\n", NULL);
// 		ft_status(127, 1);
// 	}
// }

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
			env_var = ft_strjoin("/", cmmd[0]);
		else if (cmmd[0][0] != '.')
		{
			env_var = ft_strjoin("/", cmmd[0]);
			env_var = ft_strjoin(path[i], env_var);
			env_var = ft_strjoin("/", env_var);
		}
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
	pid_t	pid;
	int 	status;
	char	*env_var;

	if (!path || !path[0])
		return ;
	env_var = ft_handler(cmmd, path);
	if (env_var)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			return ;
		}
		else if (!pid)
		{
			ft_execve(env_var, envp, cmmd);
			exit(0);
		}
		waitpid(pid, &status, 0);
		ft_status((status % 255), 1);
	}
}

char **c(char *str, int *len)
{
    char **str_r;
    int     i = 0;

    str_r = ft_split(str, ' ');
    if (!str_r)
        return (0);
    while (str_r[i])
        i++;
    (*len) += i;
    return (str_r);
}

char    **array_dupper(char **str)
{
    char **str_r;
    char     **s1;
    char     **s2;
    int     len;
    int        i;

    len = 0;
    if (str[0])
    {
        s1 = c(str[0], &len);
        if (!s1)
            return (0);
    }
    if (str[1])
    {
        s2 = c(str[1], &len);
        if (!s2)
            return (0);;
    }
    str_r = malloc(sizeof(char *) * (len + 1));
    if (!str_r)
        return (0);
    len = 0;
    if (str[0])
    {
        i = 0;
        while (s1[i])
        {
            str_r[len] = s1[i];
            len++;
            i++;
        }
    }
    if (str[1])
    {
        i = 0;
        while (s2[i])
        {
            str_r[len] = s2[i];
            len++;
            i++;
        }
    }
    if (str[2])
        str_r[len++] = str[2];
    str_r[len] = NULL;
    return (str_r);
}

void	ft_execute_cmd(t_node_arbre *tree, t_env **env, t_env **exp)
{
	int				i;
	char			**cmmd;
	char			**path;
	char			**envp;
	t_node			*tmp;
	t_node			*smp;

	i = 0;
	tmp = tree->list->top;
	smp = tree->list->top;
	envp = env_to_arr(*env);
	path = ft_split(get_path(*env), ':');
	cmmd = linkedlist_to_arr(tmp);
	while (cmmd[i])
	{
		if (smp->flag_expend == 1)
			cmmd[i] = ft_expand(*exp, cmmd[i]);
		else if (smp->flag_expend == 2)
			cmmd[i] = ft_expand(*exp, cmmd[i]);
		smp = smp->next;
		i++;
	}
	i = 0;
	smp = tree->list->top;
	while (cmmd[i])
	{
		if (ft_execute_wild(cmmd[i]) && smp->flag_wilc == 1)
			cmmd[i] = ft_strdup(ft_execute_wild(cmmd[i]));
		smp = smp->next;
		i++;
	}
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(envp, cmmd, path);
}
