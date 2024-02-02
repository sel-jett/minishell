/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:18:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/02 08:08:49 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_env *tmp)
{
	while (tmp)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}

int	cd_error(const char *path)
{
	if (chdir(path) != 0 && strncmp(path, "..", 2))
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

void	cd(const char *path, t_env **cenv)
{
	char	*b;
	char	*pwd;
	char	*temp;
	char	*temp_old;
	t_env	**pp;

	b = my_malloc(PATH_MAX + 1, 1);
	(!ft_strlen_b(path)) && (path = getenv("HOME"));
	if (cd_error(path))
		return ;
	else if (!getcwd(b, PATH_MAX))
		cd_second();
	(pp = cenv) && (temp = NULL);
	pwd = find_pwd(*cenv);
	temp_old = find_oldpwd(*cenv);
	ft_list_remove_if(cenv, "PWD", ft_strncmp_one);
	if (temp_old)
		ft_list_remove_if(cenv, "OLDPWD", ft_strncmp_two);
	temp_old = ft_strjoin("OLD", ft_strdup(pwd));
	ft_lstadd_back(cenv, env_new(temp_old));
	if (getcwd(b, PATH_MAX))
		temp = ft_strjoin("PWD=", getcwd(b, PATH_MAX));
	else
		temp = pwd_joiner(temp_old, temp, (char *)path);
	ft_lstadd_back(cenv, env_new(temp));
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
		if (cmd == NULL)
			break;
		if (!strncmp(cmd, "cd", 2))
			cd(cmd + 3, &tmp);
		else if (!strncmp(cmd, "echo -n", 7))
			echo(cmd + 8, 1);
		else if (!strncmp(cmd, "echo", 4))
			echo(cmd + 5, 0);
		else if (!strncmp(cmd, "exit", 4))
			exit(0);
		else if (!strncmp(cmd, "env", 3))
			ft_env(tmp);
		else if (!strncmp(cmd, "pwd", 3))
			printf("%s\n", find_pwd(tmp));
		else if (!strncmp(cmd, "export ", 7))
			ft_export((cmd + 7), &tmp);
	}
}
