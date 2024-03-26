/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:58:49 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 09:03:10 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_print_env_export(t_env *tmp)
{
	while (tmp)
	{
		if (tmp->key || tmp->value)
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

void	ft_env_export(t_env *env, char *key, int i)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*tmp3;
	char	*value;

	(1) && (tmp = env, tmp3 = env);
	while (tmp)
	{
		(1) && (i = 0, tmp2 = tmp);
		while (tmp2->next)
		{
			if (tmp2->key && tmp2->next->key && \
				ft_cmp(tmp2->key, tmp2->next->key) > 0)
			{
				(1) && (key = tmp2->next->key, value = tmp2->next->value);
				(1) && (i = 1, tmp2->next->key = tmp2->key);
				tmp2->next->value = tmp2->value;
				(1) && (tmp2->key = key, tmp2->value = value, tmp = tmp3);
			}
			tmp2 = tmp2->next;
		}
		(i == 0) && (tmp = tmp->next, 0);
	}
	ft_print_env_export(env);
}

void	ft_exit_required(char *str)
{
	ft_printf("exit\n", NULL);
	ft_printf("minishell: exit: ", str);
	ft_printf(": numeric argument required\n", NULL);
	ft_status(255, 1);
	exit(255);
}
