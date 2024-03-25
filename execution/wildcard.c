/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:12:25 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 02:08:21 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_checker(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '*')
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_strncmp_wild(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0 ;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen_wild_end(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '*')
		i++;
	return (i);
}

int	ft_strlen_wild_first(char *s)
{
	int	i;
	int	j;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] == '*')
		i++;
	j = 0;
	while (s[i] && s[i] != '*')
		(1) && (i++, j++);
	return (j);
}

int	ft_strlen_wild_first_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '*')
		i++;
	return (i);
}
