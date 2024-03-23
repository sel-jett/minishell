/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:59:00 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/23 06:00:06 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*exp_mlc(int *i, int *k, char *cmd)
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

char	*itoa_status(char *new_cmd)
{
	new_cmd = ft_itoa(ft_status(0, 0));
	if (!new_cmd)
		return (NULL);
	ft_status(0, 1);
	return (new_cmd);
}

char	*itoa_joiner_status(char *new_cmd, char *cmd)
{
	new_cmd = ft_itoa(ft_status(0, 0));
	if (!new_cmd)
		return (NULL);
	return (ft_strjoin(new_cmd, cmd + 2));
}

int	alpha_checker(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_alpha_3(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_expand(t_env *exp, char *cmd)
{
	char	*new_cmd;
	char	*venv;
	int		i;

	(1) && (i = 0, venv = NULL, new_cmd = NULL);
	if (!cmd)
		return (NULL);
	if (!ft_strncmp(cmd, "$?"))
	{
		return (itoa_status(new_cmd));
	}
	else if (!ft_strncmp_one(cmd, "$?"))
	{
		return (itoa_joiner_status(new_cmd, cmd));
	}
	new_cmd = my_malloc(1, 1);
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = '\0';
	new_cmd = expander(new_cmd, cmd, exp);
	if (!alpha_checker(cmd) && cmd[0] == '$')
		return (cmd);
	i = ft_strlen_b(new_cmd);
	new_cmd[i] = '\0';
	if (!new_cmd || !new_cmd[0])
		new_cmd = NULL;
	return (new_cmd);
}
