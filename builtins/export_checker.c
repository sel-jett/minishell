/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:26:29 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 01:28:08 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_alpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

static int	is_num(int c)
{
	return (c >= 48 && c <= 57);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (0);
	if (key[i] != '_' && !is_alpha(key[i]))
		return (0);
	i++;
	while (key[i])
	{
		if (key[i] != '_' && !is_alpha(key[i]) && !is_num(key[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_first(char *cmd, t_env *env)
{
	int		i;
	int		check2;
	char	*tmp;

	if (!get_key(cmd) || ft_strncmp_one("$", get_key(cmd)) == 0)
	{
		dprintf(2, "minishell: export: `%s': not a valid identifier\n", cmd);
		ft_status(1, 1);
		return (0);
	}
	tmp = ft_expand(env, get_key(cmd));
	if ((!tmp || !tmp[0]) && cmd[0] != '$')
		tmp = cmd;
	(1) && (i = 0, check2 = 0);
	if (tmp[i] != '_' && !is_alpha(tmp[i]))
	{
		if (!tmp[0])
			printf("minishell: export: `=%s':", get_value(cmd));
		else if (value_key(env, cmd))
			printf("minishell: export: `%s':",
				ft_strjoin(value_key(env, cmd), get_value(cmd)));
		else
			printf("minishell: export: `%s':", cmd);
		printf(" not a valid identifier\n");
		ft_status(1, 1);
		return (0);
	}
	i++;
	while (tmp[i] && tmp[i] != '=')
	{
		if (tmp[i] != '_' && !is_alpha(tmp[i]) && !is_num(tmp[i]))
			check2++;
		if (tmp[i + 1] && tmp[i + 1] == '=' && tmp[i] == '+')
			check2--;
		i++;
	}
	if (check2)
	{
		printf("minishell: export: `%s':", tmp);
		printf(" not a valid identifier\n");
		ft_status(1, 1);
		return (0);
	}
	return (1);
}

char	*ft_strtrim(char *cmd)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	(1) && (i = 0) && (j = -1);
	size = 0;
	while (cmd[i] <= 32)
		i++;
	while (cmd[i])
		(1) && (i++, size++);
	--i;
	while (cmd[i] <= 32)
		(1) && (--i, --size);
	str = my_malloc(size + 1, 1);
	i = 0;
	while (cmd[i] <= 32)
		i++;
	while (++j < size)
	{
		str[j] = cmd[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
