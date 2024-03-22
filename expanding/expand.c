/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:59:00 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 19:42:20 by sel-jett         ###   ########.fr       */
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

static void	ft_count_expand(int *i, int *k, char *cmd)
{
	(*i)++;
	while (is_alpha_3(cmd[*i]))
	{
		(*k)++;
		(*i)++;
	}
}

static char	*expand_malloc(int *i, int *k, char *cmd)
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

char	*ft_expand(t_env *exp, char *cmd)
{
	char	*new_cmd;
	char	*venv;
	int		k;
	int		i;
	int		l;

	(1) && (k = 0, i = 0, l = 0, venv = NULL);
	if (!cmd)
		return (NULL);
	if (!ft_strncmp(cmd, "$?"))
	{
		new_cmd = ft_itoa(ft_status(0, 0));
		if (!new_cmd)
			return (NULL);
		ft_status(0, 1);
		return (new_cmd);
	}
	else if (!ft_strncmp_one(cmd, "$?"))
	{
		new_cmd = ft_itoa(ft_status(0, 0));
		if (!new_cmd)
			return (NULL);
		new_cmd = ft_strjoin(new_cmd, cmd + 2);
		return (new_cmd);
	}
	new_cmd = my_malloc(1, 1);
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = '\0';
	while (cmd[i])
	{
		l = 0;
		if (cmd[i] && cmd[i] == '$')
		{
			ft_count_expand(&i, &k, cmd);
			venv = expand_malloc(&i, &k, cmd);
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
		venv = NULL;
		new_cmd = ft_strjoin_char(new_cmd, cmd[i]);
		if (!new_cmd)
			return (NULL);
		i++;
	}
	i = ft_strlen_b(new_cmd);
	new_cmd[i] = '\0';
	if (!new_cmd || !new_cmd[0])
		new_cmd = NULL;
	return (new_cmd);
}
