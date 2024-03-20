/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:39:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/20 04:15:32 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

static	int	echo_check(const char *path)
{
	int	i;

	i = 0;
	if (!path || !path[i])
		return (-1);
	if (path[i] == '-')
	{
		while (path[i] && path[i] > 32)
		{
			if (path[i] != 'n')
				return (0);
			i++;
		}
	}
	return (i);
}

void	echo(const char **path, int mode)
{
	int	check;

	check = 0;
	dprintf(2, "path\n");
	while (path[check])
	{
		dprintf(2, "%s\n", path[check]);
		check++;
		// if (path[check])
		// 	printf(" ");
	}
	dprintf(2, "path\n");
	exit(1);
	(void)mode;
	check = echo_check(path[0]);
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
	{
		// path++;
		while(*path)
		{
			printf("%s", *path);
			path++;
			if (*path)
				printf(" ");
		}
	}
}
