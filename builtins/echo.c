/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:39:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/29 23:00:09 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

static	int	echo_check(const char *path)
{
	int	i;

	i = 1;
	if (path[0] == '-')
	{
		while (path[i] && path[i] > 32)
		{
			if (path[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

void	echo(const char **path, int mode)
{
	int	check;

	(void)mode;
	check = echo_check(path[0]);
	if (!check)
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
	{
		path++;
		while(*path)
		{
			printf("%s", *path);
			path++;
			if (*path)
				printf(" ");
		}
	}
}
