/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 01:19:23 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 05:59:49 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sort_list(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*key;
	char	*value;

	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp;
		while (tmp2->next)
		{
			if (ft_strncmp_one(tmp2->key, tmp2->next->key) < 0)
			{
				key = ft_strdup(tmp2->key);
				value = ft_strdup(tmp2->value);
				tmp2->key = ft_strdup(tmp2->key);
				tmp2->value = ft_strdup(tmp2->value);
				tmp2->next->key = key;
				tmp2->next->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	tmp = *env;
	while (tmp)
	{
		printf("declare -x ");
		if (tmp->key)
		{
			printf("%s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"\n", tmp->value);
			else
				printf("\n");
		}
		else if (tmp->value)
			printf("=\"%s\"\n", tmp->value);
		tmp = tmp->next;
	}
}
