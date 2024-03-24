/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:43:32 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 10:17:47 by sel-jett         ###   ########.fr       */
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

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	long long int	num;
	int				signe;

	(1 == 1) && (i = 0, signe = 1, num = 0);
	if (str[i] == '-' || str[i] == '+')
	{
		(str[i] == '-') && (signe = -1);
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - 48);
		if (num * signe > LONG_MAX || num * signe < LONG_MIN)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	return (num * signe);
}

void exit_print(char *str)
{
	ft_printf("exit\n", NULL);
	ft_printf("minishell: exit: ", str);
	ft_printf(": numeric argument required", NULL);
	ft_printf("\n", NULL);
}

void	ft_exit(char *str)
{
	int	i;

	i = 0;
	while(str && str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			exit_print(str);
			ft_status(255, 1);
			exit(255);
		}
		i++;
	}
	if (str && !atoi(str))
	 	(1) && (exit_print(str), ft_status(255, 1), exit(255), 0);
	else if (str)
	{
		ft_printf("exit\n", NULL);
		exit(ft_atoi(str));
	}
	else
	{
		ft_printf("exit\n", NULL);
		exit(0);
	}
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
		ft_exit((cmd + 1)[0]);
	else if (!ft_strncmp(cmd[0], "env"))
		ft_env(*cenv);
	else if (!ft_strncmp(cmd[0], "pwd"))
	{
		printf("%s\n", find_pwd(*cenv));
		ft_status(0, 1);
	}
	else if (!ft_strncmp(cmd[0], "export"))
		ft_export((cmd + 1), cenv, exp);
	else if (!ft_strncmp(cmd[0], "unset"))
		ft_unset((cmd + 1), &cenv, &exp);
	else
		erorr_builtins(cmd[0]);
}
