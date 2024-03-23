/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:44:57 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/23 00:40:39 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	chekcer(char *data)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!data)
		return (0);
	while (data[i])
	{
		if (data[i] == '=')
			return (1);
		else if (data[i] == '+')
		{
			check = 1;
			break ;
		}
		i++;
	}
	if (!check)
		return (1);
	i++;
	if ((data[i] && data[i] != '=') || !data[i])
		return (0);
	return (1);
}

char	*get_key(char *data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	if (!chekcer(data))
	{
		return (NULL);
	}
	if (data)
		while (data[i] && data[i] != '=' && data[i] != '+')
			i++;
	str = my_malloc(i + 1, 1);
	if (!str)
		return (NULL);
	while (++j < i)
		str[j] = data[j];
	str[i] = '\0';
	return (str);
}

char	*get_value(char *data)
{
	int		i;
	int		j;
	int		s;
	char	*str;

	if (!data)
		return (NULL);
	i = 0;
	j = ft_strlen_b(data);
	while (data[i] && data[i] != '=')
		i++;
	if (!data[i])
		return (NULL);
	(1) && (i++, s = j - i);
	str = my_malloc(s + 1, 1);
	if (!str)
		return (NULL);
	j = -1;
	while (++j < s)
	{
		str[j] = data[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

static int	check_key(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (i > 0 && cmd[i] == '=' && cmd[i - 1] == '+')
		return (1);
	return (0);
}

t_env	*env_new(char *data, t_env *tmp)
{
	t_env	*node;
	char	*str;
	char	*gt_value;
	char	*value_of;

	node = my_malloc(sizeof(t_env), 1);
	if (!node || !get_key(data))
		return (NULL);
	str = ft_expand(tmp, get_key(data));
	(!str || !str[0]) && (str = get_key(data));
	value_of = value_key(tmp, str);
	if (check_key(data) && value_of)
	{
		gt_value = get_value(data);
		(node->key = str) && (node->next = NULL);
		node->value = ft_strjoin(value_of, gt_value);
		if (!node->value)
			return (NULL);
		ft_list_remove_if(&tmp, str, ft_strncmp_one);
		return (node);
	}
	else
		node->value = get_value(data);
	(node->key = str) && (node->next = NULL);
	return (node);
}
