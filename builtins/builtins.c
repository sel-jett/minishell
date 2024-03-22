/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:43:32 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/21 22:46:14 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_getter(char	*temp, char	*temp_old, char *b, const char **path)
{
	if (getcwd(b, PATH_MAX))
	{
		temp = ft_strjoin("PWD=", getcwd(b, PATH_MAX));
		if (!temp)
			return (NULL);
	}
	else
	{
		temp = pwd_joiner(temp_old, temp, (char *)path[0]);
		if (!temp)
			return (NULL);
	}
	return (temp);
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

void	erorr_builtins(char *cmd)
{
	ft_printf("minishell: ", cmd);
	ft_printf(":", " command not found");
	ft_printf("\n", NULL);
	ft_status(127, 1);
}

void	ft_builtin(char **cmd, t_env **cenv, t_env **exp)
{
	t_env	*tmp;

	tmp = *cenv;
	if (!ft_strncmp(cmd[0], "cd"))
		cd((const char **)(cmd + 1), cenv, exp);
	else if (!ft_strncmp(cmd[0], "echo"))
	{
		echo((const char **)(cmd + 1), 0);
		ft_status(0, 1);
	}
	else if (!ft_strncmp(cmd[0], "exit"))
		exit(ft_status(0, 0));
	else if (!ft_strncmp(cmd[0], "env"))
		ft_env(*cenv);
	else if (!ft_strncmp(cmd[0], "pwd"))
	{
		printf("%s\n", value_key(tmp, "PWD"));
		ft_status(0, 1);
	}
	else if (!ft_strncmp(cmd[0], "export"))
		ft_export((cmd + 1), cenv, exp);
	else if (!ft_strncmp(cmd[0], "unset"))
		ft_unset((cmd + 1), cenv, exp);
	else
		erorr_builtins(cmd[0]);
}
