/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:18:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/01 10:56:58 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>

void	cd(const char *path, t_env *cenv)
{
	char	*b;

	b = my_malloc(PATH_MAX + 1, 1);
	if (!ft_strlen_b(path))
		path = getenv("HOME");
	if (chdir(path) != 0 && strncmp(path, "..", 2))
	{
		ft_fpintf("mminishell: cd");
		ft_fpintf(path);
		(1) && (ft_fpintf(": "), perror(""), 1);
		return ;
	}
	else if (!getcwd(b, PATH_MAX))
	{
		ft_fpintf("cd: error retrieving current directory: getcwd: ");
		ft_fpintf("cannot access parent directories: No such file or directory");
	}
	cenv->oldpwd = ft_strdup(cenv->pwd);
	if (getcwd(b, PATH_MAX))
		cenv->pwd = getcwd(b, PATH_MAX);
	else
	{
		cenv->pwd = ft_strjoin(cenv->oldpwd, "/");
		cenv->pwd = ft_strjoin(cenv->pwd, (char *)path);
	}
}

void	env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	char	s[100];
	char	*cmd;
	t_env	*cenv;

	cenv = my_malloc(sizeof(cenv), 1);
	cenv->oldpwd = NULL;
	cenv->pwd = getcwd(s, 100);
	while (1)
	{
		cmd = readline("\033[0;32mminishell > \033[0m");
		if (cmd == NULL)
			break;
		if (!strncmp(cmd, "cd", 2))
			cd(cmd + 3, cenv);
		else if (!strncmp(cmd, "echo -n", 7))
			echo(cmd + 8, 1);
		else if (!strncmp(cmd, "echo", 4))
			echo(cmd + 5, 0);
		else if (!strncmp(cmd, "exit", 4))
			exit(0);
		else if (!strncmp(cmd, "env", 3))
			env();
		else if (!strncmp(cmd, "pwd", 3))
			printf("%s", cenv->pwd);
	}
}
