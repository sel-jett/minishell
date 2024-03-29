/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:26:29 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 10:06:35 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_alpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	is_num(int c)
{
	return (c >= 48 && c <= 57);
}

int	valid_identifier(char *tmp, int i, int check2)
{
	i++;
	while (tmp && tmp[i] && tmp[i] != '=')
	{
		if (tmp[i] != '_' && !is_alpha(tmp[i]) && \
			!is_num(tmp[i]) && tmp[i] != '$')
			check2++;
		if (tmp[i + 1] && tmp[i + 1] == '=' && tmp[i] == '+')
			check2--;
		i++;
	}
	if (tmp && check2)
	{
		printf("minishell: export: `%s':", tmp);
		printf(" not a valid identifier\n");
		ft_status(1, 1);
		return (0);
	}
	return (1);
}

int	check_first(char *cmd, t_env *env)
{
	t_variable	v;

	if (!get_key(cmd) || ft_strncmp_one("$", get_key(cmd)) == 0)
	{
		write(2, "minishell: export: `", 20);
		(1) && (write(2, cmd, ft_strlen(cmd)), write(2, "': not a", 8));
		return (write(2, " valid identifier\n", 18), ft_status(1, 1), 0);
	}
	v.tmp = ft_expand(env, get_key(cmd));
	((!v.tmp || !v.tmp[0]) && cmd[0] != '$') && (v.tmp = cmd);
	(1) && (v.i = 0, v.check2 = 0);
	if (v.tmp && v.tmp[v.i] != '_' && !is_alpha(v.tmp[v.i]))
	{
		if (!v.tmp[0] && get_value(cmd))
			printf("minishell: export: `=%s':", get_value(cmd));
		else if (!v.tmp[0] && !get_value(cmd))
			printf("minishell: export: `':");
		else if (value_key(env, cmd))
			printf("minishell: export: `%s':", \
				ft_strjoin(value_key(env, cmd), get_value(cmd)));
		else
			printf("minishell: export: `%s':", cmd);
		return (printf(" not a valid identifier\n"), ft_status(1, 1), 0);
	}
	return (valid_identifier(v.tmp, v.i, v.check2));
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
