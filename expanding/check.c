/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:01:23 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 21:10:12 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	dollar_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*exp_mlc(int *i, int *k, char *cmd)
{
	int		l;
	char	*venv;

	l = 0;
	venv = my_malloc(*k + 1, 1);
	if (!venv)
		return (NULL);
	while (*k > 0)
	{
		if (!is_alpha_3(cmd[*i - *k]))
			break ;
		venv[l] = cmd[*i - *k];
		l++;
		(*k)--;
	}
	venv[l] = '\0';
	return (venv);
}

char	*expander(char *new_cmd, char *cmd, t_env *exp)
{
	int		i;
	int		k;
	char	*venv;

	(1) && (i = 0, k = 0);
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == '$')
		{
			(1) && (ct_exp(&i, &k, cmd), venv = exp_mlc(&i, &k, cmd));
			if (!venv)
				return (NULL);
			if (value_key(exp, venv))
			{
				new_cmd = ft_strjoin(new_cmd, value_key(exp, venv));
				if (!new_cmd)
					return (NULL);
			}
			continue ;
		}
		(1) && (venv = NULL, new_cmd = ft_strjoin_char(new_cmd, cmd[i]));
		if (i++ && !new_cmd)
			return (NULL);
	}
	return (new_cmd);
}
