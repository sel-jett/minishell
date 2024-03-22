/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:58:34 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 19:58:54 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	length(char *s, char *str)
{
	int				j;
	int				i;
	unsigned long	len;

	j = 0;
	i = 0;
	while (str[i] && str[i] == '*')
		i++;
	len = strlen(str + i);
	while (strlen(s + j) != len)
		j++;
	return (j);
}

int	only_wild(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}
