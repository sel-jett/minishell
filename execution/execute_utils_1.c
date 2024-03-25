/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:53:26 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 17:38:32 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	first_key_checker(char *cmmd)
{
	int	i;

	i = 0;
	if (cmmd[i] && cmmd[i] == '$' && cmmd[i + 1] && !is_alpha_3(cmmd[i + 1]) \
		&& cmmd[i + 1] != '?')
		return (1);
	return (0);
}

int	contain_wild(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

void	array_structer_2(char **str)
{
	int	i;
	int	n;

	i = 0;
	while (str && str[i] && str[i][0])
	{
		n = ft_strlen(str[i]) - 1;
		if (str[i] && str[i][n] && str[i][n] == '\\')
			str[i][n] = '\0';
		i++;
	}
}
