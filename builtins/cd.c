/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:18:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/08 15:38:09 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	printf("path: %s\n", path);
	if (chdir(path) != 0 && ft_strncmp_one((char *)path, ".."))
	{
		ft_fpintf("mminishell: cd");
		ft_fpintf(path);
		ft_fpintf(": ");
		perror("");
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
		else if (path[i] != '-')
			return (1);
		i++;
	}
	if (check == 1 || (path[i - 1] && path[i - 2] && path[i - 1] == '-' && path[i - 2] == '-'))
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

void	ft_second_cd(t_env **cenv, char *b, const char ** path)
{
	char	*pwd;
	char	*temp;
	char	*temp_old;

	temp = NULL;
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
		temp = pwd_joiner(temp_old, temp, (char *)path[0]);
	ft_lstadd_back(cenv, env_new(temp, NULL));
}

void	cd(const char **path, t_env **cenv)
{
	char	*b;

	b = my_malloc(PATH_MAX + 1, 1);
	if (!cd_home(path[0]))
		path[0] = value_key(*cenv, "HOME");
	else if (!cd_old(path[0]))
	{
		path[0] = value_key(*cenv, "OLDPWD");
		if (!path[0])
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
	}
	if (cd_error(path[0]))
		return ;
	else if (!getcwd(b, PATH_MAX))
		cd_second();
	ft_second_cd(cenv, b, path);
}

void	ft_printf(const char *str, const char *str2)
{
	if (str)
	{
		while (*str)
		{
			write(2, str, 1);
			str++;
		}
	}
	if (str2)
	{
		while (*str2)
		{
			write(2, str2, 1);
			str2++;
		}
	}
}

void	ft_builtin(char **cmd, t_env **cenv, t_env **exp)
{
	t_env	*tmp;

	tmp = *cenv;
	if (!ft_strncmp(cmd[0], "cd"))
		cd((const char **)(cmd + 1), &tmp);
	else if (!ft_strncmp(cmd[0], "echo"))
		echo((const char **)(cmd + 1), 0);
	else if (!ft_strncmp(cmd[0], "exit"))
		exit(0);
	else if (!ft_strncmp(cmd[0], "env"))
		ft_env(tmp);
	else if (!ft_strncmp(cmd[0], "pwd"))
		printf("%s\n", value_key(tmp, "PWD"));
	else if (!ft_strncmp(cmd[0], "export"))
		ft_export((cmd + 1), cenv, exp);
	else if (!ft_strncmp(cmd[0], "unset"))
		ft_unset((cmd + 1), &tmp, exp);
	else
	{
		ft_printf("minishell: ", cmd[0]);
		ft_printf(":", " command not found");
		ft_printf("\n", NULL);
		ft_status(127, 1);
	}
}
