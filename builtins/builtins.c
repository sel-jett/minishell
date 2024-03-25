/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:43:32 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 12:51:17 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_getter(char	*temp, t_env *cenv, int i, const char **path)
{
	if (i == 1)
	{
		temp = ft_strjoin("PWD=", getcwd(0, 0));
		ft_list_remove_if(&cenv, "PWD", ft_strncmp_one);
		if (!temp)
			return (NULL);
	}
	else
	{
		temp = ft_strjoin("/", (char *)path[0]);
		temp = ft_strjoin(ft_strdup(value_key(cenv, "PWD")), temp);
		temp = ft_strjoin("PWD=", temp);
		ft_list_remove_if(&cenv, "PWD", ft_strncmp_one);
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
	unsigned long long	num;
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
		if (num > 9223372036854775807 && signe == -1)
			return (-1);
		else if (num > 9223372036854775807)
			return (-1);
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

void	ft_exit(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !str[i])
	{
		ft_printf("exit\n", NULL);
		exit(ft_status(0, 0));
	}
	while (str[i][j])
	{
		if (j == 0 && (str[i][0] == '-' || str[i][0] == '+'))
		{
			j++;
			continue ;
		}
		if (ft_isdigit(str[i][j]))
			j++;
		else
			break ;
	}
	if (str[i + 1] && !str[i][j])
	{
		ft_printf("exit\n", NULL);
		ft_printf("minishell: exit: ", NULL);
		ft_printf(": too many arguments\n", NULL);
		ft_status(1, 1);
		return ;
	}
	else if (str[i][j])
	{
		ft_printf("exit\n", NULL);
		ft_printf("minishell: exit: ", str[0]);
		ft_printf(": numeric argument required\n", NULL);
		ft_status(255, 1);
		exit(255) ;
	}
	if (str && !atoi(str[0]))
	 	(1) && (exit_print(str[0]), ft_status(255, 1), exit(255), 0);
	else if (str)
	{
		ft_printf("exit2\n", NULL);
		dprintf(2, "exit: %d\n", (ft_atoi(str[0]) % 256));
		ft_status(ft_atoi(str[0]) % 256, 1);
		exit(ft_atoi(str[0]) % 256);
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
		ft_exit((cmd + 1));
	else if (!ft_strncmp(cmd[0], "env"))
		ft_env(*cenv);
	else if (!ft_strncmp(cmd[0], "pwd"))
	{
		printf("%s\n", getcwd(0, 0));
		ft_status(0, 1);
	}
	else if (!ft_strncmp(cmd[0], "export"))
		ft_export((cmd + 1), cenv, exp);
	else if (!ft_strncmp(cmd[0], "unset"))
		ft_unset((cmd + 1), cenv, exp);
	else
		erorr_builtins(cmd[0]);
}
