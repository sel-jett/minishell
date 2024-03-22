/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:06:50 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/21 23:13:43 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (!env_new(env[i], NULL))
			return (NULL);
		ft_lstadd_back(&lst, env_new(env[i], NULL));
		i++;
	}
	ft_list_remove_if(&lst, "OLDPWD", ft_strncmp_one);
	return (lst);
}
