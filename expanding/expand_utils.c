/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:50:03 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 21:54:29 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_expand(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == '$')
		{
			while (cmd[i] && cmd[i] != '-')
				i++;
			continue ;
		}
		j++;
		i++;
	}
	return (j);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen_b(s1) + 1;
	str = my_malloc(size + 1, 1);
	if (!str)
		return (NULL);
	i = 0;
	size = 0;
	while (s1 && s1[i])
		(1) && (str[i] = s1[i], i++);
	str[i] = s2;
	str[i + 1] = '\0';
	return (str);
}

void	ct_exp(int *i, int *k, char *cmd)
{
	(*i)++;
	while (is_alpha_3(cmd[*i]))
	{
		(*k)++;
		(*i)++;
	}
}
