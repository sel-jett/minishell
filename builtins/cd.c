/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:18:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/01 01:50:44 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
// #include <readline/history.h>

void	ft_fpintf(const char *msg)
{
	int	i;
	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	write(2, ": ", 2);
}


int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

void	echo(const char *path, int mode)
{
	if (mode)
		printf("%s", path);
	else
		printf("%s\n", path);
}

void	cd(const char *path)
{
	char s[100];

	if (!ft_strlen(path))
		path = getenv("HOME");
	printf("%s\n", getcwd(s, 100));
	if (!getcwd(s, 100))
	{
		ft_fpintf("cd: error retrieving current directory: getcwd: ");
		ft_fpintf("cannot access parent directories: No such file or directory");
	}
	if (chdir(path) != 0)
	{
		ft_fpintf("mminishell: cd");
		ft_fpintf(path);
		perror("");
	}
	printf("%s\n", getcwd(s, 100));
}

int main (int ac, char **av)
{
	(void)ac;
	char *cmd;
	while (1)
	{
		cmd = readline("\033[0;32mminishell > \033[0m");
		if (cmd == NULL)
			break;
		if (!strncmp(cmd, "cd", 2))
			cd(cmd + 3);
		else if (!strncmp(cmd, "echo -n", 7))
			echo(cmd + 8, 1);
		else if (!strncmp(cmd, "echo", 4))
			echo(cmd + 5, 0);
		else if (!strncmp(cmd, "exit", 4))
			exit(0);
	}
}
