/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:25:26 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 08:26:15 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_bi(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_func_string(char **str, int i)
{
	char	**tmp;
	int		len;
	int		j;

	len = ft_strlen_bi(str);
	tmp = my_malloc((len * 8), 1);
	if (!tmp)
		return (NULL);
	len = 0;
	j = 0;
	while (str[len])
	{
		if (i == len)
		{
			len += 1;
			continue ;
		}
		tmp[j] = str[len];
		len++;
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char	**array_structer(char **str)
{
	int	tab[2];

	(1) && (tab[0] = 0, tab[1] = 0);
	while (str && str[tab[0]] && str[tab[0]][0])
	{
		while (str[tab[0]][tab[1]])
		{
			if (str[tab[0]][0] == '\\')
			{
				if (str[tab[0] + 1])
				{
					(1) && (str = ft_func_string(str, tab[0]), tab[0] = 0);
					continue ;
				}
				else
				{
					str[tab[0]] = NULL;
					break ;
				}
			}
			tab[1]++;
		}
		(1) && (tab[1] = 0, tab[0]++);
	}
	return (str = joyner(str), str);
}

int	array_checker(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\v' || str[i][j] == '\\' || str[i][j] == -32)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strlen_tri(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
