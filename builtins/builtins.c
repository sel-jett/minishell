/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:43:32 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 05:38:22 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_required(char *str)
{
	ft_printf("exit\n", NULL);
	ft_printf("minishell: exit: ", str);
	ft_printf(": numeric argument required\n", NULL);
	ft_status(255, 1);
	exit(255);
}

int	ft_exit_arg(char *str, char c)
{
	if (str && !c)
	{
		ft_printf("exit\n", NULL);
		ft_printf("minishell: exit: ", ": too many arguments\n");
		ft_status(1, 1);
		return (0);
	}
	return (1);
}

void	ft_exit_num(char *str)
{
	ft_printf("minishell: exit: ", str);
	ft_printf(": numeric argument required\n", NULL);
	ft_status(255, 1);
	exit(255);
}

void	ft_exit_loop(char **str, int *i, int *j)
{
	while (str[*i][*j])
	{
		if (*j == 0 && (str[*i][0] == '-' || str[*i][0] == '+'))
		{
			(*j)++;
			continue ;
		}
		if (ft_isdigit(str[*i][*j]))
			(*j)++;
		else
			break ;
	}
}

void	ft_exit(char **str)
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	if (!str || !str[i])
		(1) && (ft_printf("exit\n", NULL), exit(ft_status(0, 0)), 0);
	ft_exit_loop(str, &i, &j);
	if (!ft_exit_arg(str[i + 1], str[i][j]))
		return ;
	else if (str[i][j])
		ft_exit_required(str[i]);
	if (str && !atoi(str[0]))
		(1) && (exit_print(str[0]), ft_status(255, 1), exit(255), 0);
	else if (str)
	{
		ft_printf("exit\n", NULL);
		ft_status(ft_atoi(str[0]) % 256, 1);
		if (ft_atoi(str[0]) < 0)
			ft_exit_num(str[0]);
		else
			exit(ft_atoi(str[0]) % 256);
	}
}

void	ft_builtin(char **cmd, t_env **cenv, t_env **exp)
{
	t_env	*tmp;
	int i, j, k;

	(1) && (i = 0, j = 0, k = 0);
	tmp = *cenv;
	if (!ft_strncmp((array_31(ft_31_spliter(cmd, i, j, k)))[0], "cd"))
		cd((const char **)array_31(ft_31_spliter(cmd + 1, i, j, k)), cenv, exp);
	else if (!ft_strncmp(array_31(ft_31_spliter(cmd, i, j, k))[0], "echo"))
		(1) && (echo((const char **)array_31(ft_31_spliter(cmd + 1, i, j, k)), 0), ft_status(0, 1), 0);
	else if (!ft_strncmp(array_31(ft_31_spliter(cmd, i, j, k))[0], "exit"))
		ft_exit(array_31(ft_31_spliter(cmd + 1, i, j, k)));
	else if (!ft_strncmp(array_31(ft_31_spliter(cmd, i, j, k))[0], "env"))
		ft_env(*cenv);
	else if (!ft_strncmp(array_31(ft_31_spliter(cmd, i, j, k))[0], "pwd"))
	{
		(getcwd(0, 0)) && (printf("%s\n", getcwd(0, 0)));
		(!getcwd(0, 0)) && (printf("%s\n", value_key(*cenv, "PWD")));
		ft_status(0, 1);
	}
	else if (!ft_strncmp(array_31(ft_31_spliter(cmd, i, j, k))[0], "export"))
		ft_export(array_31(cmd + 1), cenv, exp);
	else if (!ft_strncmp(array_31(ft_31_spliter(cmd, i, j, k))[0], "unset"))
		ft_unset(array_31(ft_31_spliter(cmd + 1, i, j, k)), cenv, exp);
	else
		erorr_builtins(array_31(ft_31_spliter(cmd, i, j, k))[0]);
}
