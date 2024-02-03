/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:39:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/03 04:09:39 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static	int	echo_check(const char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] > 32)
	{
		if (path[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(const char *path, int mode)
{
	int	check;

	check = 0;
	if (mode)
	{
		check = echo_check(path);
		if (!check)
			printf("-n%s\n", path);
		else
		{
			check = 0;
			while (*path == 'n')
				path++;
			if (path)
				while (*path <= 32)
					path++;
			printf("%s", path);
		}
	}
	else
		printf("%s\n", path);
}
