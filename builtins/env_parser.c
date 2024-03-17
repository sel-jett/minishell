/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:44:57 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/17 06:26:51 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtins.h"
#include "../includes/minishell.h"

char	*value_key(t_env *tmp, char *key)
{
	while (tmp)
	{
		if (!ft_strncmp_one(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_key(char *data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	if (data)
		while (data[i] && data[i] != '=' && data[i] != '+')
			i++;
	str = my_malloc(i + 1, 1);
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
	i++;
	s = j - i;
	str = my_malloc(s + 1, 1);
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

	node = my_malloc(sizeof(t_env), 1);
	str = get_key(data);
	if (check_key(data))
	{
		node->key = get_key(data);
		node->value = ft_strjoin(get_value(data), value_key(tmp, str));
		ft_list_remove_if(&tmp, str, ft_strncmp_one);
	}
	else
		node->value = get_value(data);
	node->key = str;
		// dprintf(2, "node->value = %s\n", node->value);
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*node;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	node = ft_lstlast(*lst);
	node->next = new;
}

void	ft_list_remove_if(t_env **begin_list, void *data_ref, int (*cmp)())
{
	t_env	*cur;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	if (cmp(cur->key, data_ref) == 0)
	{
		*begin_list = cur->next;
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		cur = *begin_list;
		ft_list_remove_if(&cur->next, data_ref, cmp);
	}
}

t_env	*ft_env_parser(char **env)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = NULL;
	while (env[i])
	{
		ft_lstadd_back(&lst, env_new(env[i], NULL));
		i++;
	}
	ft_list_remove_if(&lst, "OLDPWD", ft_strncmp_one);
	return (lst);
}
