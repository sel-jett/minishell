/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:18:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/03 23:02:45 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_env *tmp)
{
	while (tmp)
	{
		printf("%s", tmp->key);
		printf("=");
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

int	cd_error(const char *path)
{
	if (chdir(path) != 0 && ft_strncmp_one((char *)path, ".."))
	{
		ft_fpintf("mminishell: cd");
		ft_fpintf(path);
		(1) && (ft_fpintf(": "), perror(""), 0);
		return (1);
	}
	return (0);
}

void	cd_second(void)
{
	ft_fpintf("cd: error retrieving current directory: getcwd: ");
	ft_fpintf("cannot access parent directories: ");
	ft_fpintf("No such file or directory\n");
}

int	cd_home(const char *path)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!ft_strlen_b(path))
		return (0);
	while (path[i])
	{
		if (path[i] == '~')
			check++;
		else if (path[i] <= 32)
		{
			i++;
			continue ;
		}
		else
			return (1);
		i++;
	}
	if (check == 1)
		return (0);
	return (1);
}

int	cd_old(const char *path)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!ft_strlen_b(path))
		return (0);
	while (path[i])
	{
		if (path[i] == '-')
			check++;
		else if (path[i] <= 32)
		{
			i++;
			continue ;
		}
		else
			return (1);
		i++;
	}
	if (check == 1)
		return (0);
	return (1);
}

void	cd(const char *path, t_env **cenv)
{
	char	*b;
	char	*pwd;
	char	*temp;
	char	*temp_old;
	t_env	**pp;

	b = my_malloc(PATH_MAX + 1, 1);
	(!cd_home(path)) && (path = getenv("HOME"));
	if (!cd_old(path))
	{
		path = value_key(*cenv, "OLDPWD");
		if (!path)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
	}
	if (cd_error(path))
		return ;
	else if (!getcwd(b, PATH_MAX))
		cd_second();
	(1) && (pp = cenv, temp = NULL);
	pwd = find_pwd(*cenv);
	temp_old = find_oldpwd(*cenv);
	ft_list_remove_if(cenv, "PWD", ft_strncmp_one);
	if (temp_old)
		ft_list_remove_if(cenv, "OLDPWD", ft_strncmp_one);
	temp_old = ft_strjoin("OLD", ft_strdup(pwd));
	ft_lstadd_back(cenv, env_new(temp_old, NULL));
	if (getcwd(b, PATH_MAX))
		temp = ft_strjoin("PWD=", getcwd(b, PATH_MAX));
	else
		temp = pwd_joiner(temp_old, temp, (char *)path);
	ft_lstadd_back(cenv, env_new(temp, NULL));
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*cmd;
	t_env	*tmp;
	t_env	*cenv;

	cenv = ft_env_parser(env);
	tmp = cenv;
	while (1)
	{
		cmd = readline("\033[0;32mminishell > \033[0m");
		if (!strncmp(cmd, "cd", 2))
			cd(cmd + 3, &tmp);
		else if (!ft_strncmp_one(cmd, "echo -n"))
			echo(cmd + 6, 1);
		else if (!ft_strncmp_one(cmd, "echo"))
			echo(cmd + 5, 0);
		else if (!ft_strncmp_one(cmd, "exit"))
			exit(0);
		else if (!ft_strncmp_one(cmd, "env"))
			ft_env(tmp);
		else if (!ft_strncmp_one(cmd, "pwd"))
			printf("%s\n", value_key(tmp, "PWD"));
		else if (!ft_strncmp_one(cmd, "export"))
			ft_export(cmd + 7, &tmp);
		else if (!ft_strncmp_one(cmd, "unset"))
			ft_unset(cmd + 6, &tmp);
	}
}
