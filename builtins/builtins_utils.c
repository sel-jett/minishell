/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:01:57 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 16:38:14 by sel-jett         ###   ########.fr       */
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
	int					i;
	unsigned long long	num;
	int					signe;

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
