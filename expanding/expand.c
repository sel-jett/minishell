/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:59:00 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/15 06:46:05 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_expand(char *cmd)
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
			continue;
		}
		j++;
		i++;
	}
	return j;
}

char	*ft_strjoin_char(char *s1, char s2)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen_b(s1) + 1;
	str = malloc(size + 1);
	i = 0;
	size = 0;
	while (s1 && s1[i])
		(1) && (str[i] = s1[i], i++);
	str[i] = s2;
	str[i + 1] = '\0';
	return (str);
}

static void	ft_norminette(int *i, int *k, char *cmd)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '-')
	{
		(*k)++;
		(*i)++;
	}
}

static char	*ft_second_norminette(int *i, int *k, char *cmd)
{
	int l = 0;
	char *venv;
	venv = malloc(*k + 1);
	while (*k > 0)
	{
		if (cmd[*i - *k] == '-')
			break;
		venv[l] = cmd[*i - *k];
		l++;
		(*k)--;
	}
	venv[l] = '\0';
	return (venv);
}

char	*ft_expand(char *cmd)
{
	char	*new_cmd;
	char	*venv;
	int		k;
	int		i;
	int		j;
	int		l;

	(1) && (k = 0, i = 0, j = 0, l = 0, venv = NULL);
	if (!ft_strncmp(cmd, "$?"))
	{
		new_cmd = ft_itoa(ft_status(0, 0));
		return (new_cmd);
	}
	(1) && (new_cmd = malloc(1), new_cmd[0] = '\0');
	while (cmd[i])
	{
		l = 0;
		if (cmd[i] && cmd[i] == '$')
		{
			ft_norminette(&i, &k, cmd);
			venv = ft_second_norminette(&i, &k, cmd);
			if (getenv(venv))
				new_cmd = ft_strjoin(new_cmd, getenv(venv));
			j += ft_strlen_b(getenv(venv));
			continue;
		}
		j += ft_strlen_b(venv);
		new_cmd = ft_strjoin_char(new_cmd, cmd[i]);
		j++;
		i++;
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}
