/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:05:40 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 08:47:13 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_error(char *path)
{
	int	i;

	i = chdir(path);
	if (i != 0 && ft_strncmp_one((char *)path, ".."))
	{
		ft_fpintf("mminishell: cd: ");
		ft_fpintf(path);
		ft_fpintf(": ");
		perror("");
		ft_status(1, 1);
		return (1);
	}
	else if (i == 0)
	{
		ft_status(0, 1);
		return (0);
	}
	return (0);
}

void	cd_second(void)
{
	ft_fpintf("cd: error retrieving current directory: getcwd: ");
	ft_fpintf("cannot access parent directories: ");
	ft_fpintf("No such file or directory\n");
	ft_status(1, 1);
}

int	cd_old(char *path)
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

int	cd_home(char *path)
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
	if (check == 1 || (path[i - 1] && path[i - 2] && \
		path[i - 1] == '-' && path[i - 2] == '-'))
		return (0);
	return (1);
}
