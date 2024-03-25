/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:39:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 13:50:40 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

static	int	echo_check(const char **path)
{
	int	i;
	int	j;

	i = 0;
	if (!path || !path[0])
		return (-1);
	if (path[0][0] == '-')
	{
		while (path[i] && path[i][0] == '-')
		{
			j = 1;
			while (path[i][j] && path[i][j] > 32)
			{
				if (path[i][j] != 'n')
				{
					if (i > 0)
						(1) && (j = -1);
					break;
				}
				j++;
			}
			if (j == -1)
				break ;
			i++;
		}
	}
	else
		return (0);
	if (i > 0)
		return (i);
	return (1);
}

void	echo_n(int check, const char **path)
{
	path = path + check;
	while (*path)
	{
		printf("%s", *path);
		path++;
		if (*path)
			printf(" ");
	}
}

void	echo(const char **path, int mode)
{
	int	check;

	check = 0;
	(void)mode;
	check = echo_check(path);
	if (check == -1)
	{
		printf("\n");
		return ;
	}
	else if (!check)
	{
		check = 0;
		while (path[check])
		{
			printf("%s", path[check]);
			check++;
			if (path[check])
				printf(" ");
		}
		printf("\n");
	}
	else
		echo_n(check, path);
}
