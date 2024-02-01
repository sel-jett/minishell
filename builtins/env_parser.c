/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:44:57 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/01 23:53:42 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*env_new(char *data)
{
	t_env	*node;

	node = my_malloc(sizeof(t_env), 1);
	node->data = data;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (0);
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
	if (cmp(cur->data, data_ref) == 0)
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
	while (env[i])
	{
		ft_lstadd_back(&lst, env_new(env[i]));
		i++;
	}
	return (lst);
}
