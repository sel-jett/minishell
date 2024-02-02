/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:26:29 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/02 08:07:52 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_alpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

static int	is_num(int c)
{
	return (c >= 48 && c <= 57);
}

int	check_first(char *cmd)
{
	int	i;
	int	check2;

	i = 0;
	check2 = 0;
	if (cmd[i] != '_' && !is_alpha(cmd[i]))
	{
		printf("minishell: export: `%s':", cmd);
		printf(" not a valid identifier\n");
		return (0);
	}
	i++;
	while (cmd[i] != '=')
	{
		if (cmd[i] != '_' && !is_alpha(cmd[i]) && !is_num(cmd[i]))
			check2++;
		i++;
	}
	if (check2)
	{
		printf("minishell: export: `%s':", cmd);
		printf(" not a valid identifier\n");
		return (0);
	}
	return (1);
}

char	*ft_strtrim(char *cmd)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	j = -1;
	size = 0;
	while(cmd[i] <= 32)
		i++;
	while (cmd[i])
		(1) && (i++, size++);
	--i;
	while (cmd[i] <= 32)
		(1) && (--i, --size);
	str = my_malloc(size + 1, 1);
	i = 0;
	while(cmd[i] <= 32)
		i++;
	while (++j < size)
	{
		str[j] = cmd[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
