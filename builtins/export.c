/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:03:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/02 08:23:11 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*grep_first(char *cmd)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (cmd[i] != '=')
		i++;
	str = my_malloc(i + 1, 1);
	j = -1;
	while (++j < i)
		str[j] = cmd[i];
	return (str);
}


void	ft_export(char *cmd, t_env **cnev)
{
	cmd = ft_strtrim(cmd);
	if (!check_first(cmd))
		return;
	ft_list_remove_if(cenv, grep_first(cmd), ft_strncmp_one);
	ft_lstadd_back(cnev, env_new(cmd));
}
