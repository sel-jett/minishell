/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:37:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 07:49:58 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

void	ft_fpintf(const char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

int	ft_strlen_b(const char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	char	*str;
	int		i;

	size = ft_strlen_b(s1) + ft_strlen_b(s2);
	str = my_malloc(size + 1, 1);
	i = 0;
	size = 0;
	while (s1 && s1[i])
		(1) && (str[i] = s1[i], i++);
	while (s2 && s2[size])
		(1) && (str[i + size] = s2[size], size++);
	str[i + size] = '\0';
	return (str);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		size;
	char	*str;
	int		i;

	size = ft_strlen_b(s1) + ft_strlen_b(s2);
	if (!size)
		return (0);
	str = malloc(size + 1);
	i = 0;
	size = 0;
	while (s1 && s1[i])
		(1) && (str[i] = s1[i], i++);
	while (s2 && s2[size])
		(1) && (str[i + size] = s2[size], size++);
	str[i + size] = '\0';
	return (free(s1), str);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = my_malloc(ft_strlen_b(s) + 1, 1);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
