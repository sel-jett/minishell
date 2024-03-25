/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:06:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 17:30:22 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**checkerr(char *str, int *len)
{
	char	**str_r;
	int		i;

	i = 0;
	str_r = ft_split(str, ' ');
	if (!str_r)
		return (NULL);
	while (str_r[i])
		i++;
	(*len) += i;
	return (str_r);
}

char	**ft_spliter(char **str, char	**str_r)
{
	int		i;
	int		j;
	int		len;
	char	**s;

	i = 0;
	len = 0;
	while (str[i])
	{
		j = 0;
		s = ft_split(str[i], ' ');
		if (!s)
			return (NULL);
		while (s[j])
		{
			str_r[len] = s[j];
			len++;
			j++;
		}
		i++;
	}
	str_r[len] = NULL;
	return (str_r);
}

char	**array_dupper(char **str)
{
	char	**str_r;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		checkerr(str[i], &len);
		if (!str[i])
			return (NULL);
		i++;
	}
	str_r = my_malloc((sizeof(char *) * (len + 1)), 1);
	if (!str_r)
		return (NULL);
	return (ft_spliter(str, str_r));
}

void	backslach_filler(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "\v"))
			str[i][0] = '\0';
		i++;
	}
}
