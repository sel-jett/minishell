/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:27:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 20:45:53 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_alpha_4(char c)
{
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| c == '_'))
		return (0);
	return (1);
}

int	is_alpha_2(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z') \
			|| c[i] == '_' || (c[i] >= '0' && c[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

t_env	**fun(t_env **node, char *key)
{
	t_env	*tmp1;

	if (*node == NULL)
		return (NULL);
	if ((*node)->key && ft_strcmp((*node)->key, key))
	{
		if (*node == NULL)
			return (NULL);
		(*node)->key = NULL;
		(*node)->value = NULL;
		return (&(*node)->next);
	}
	tmp1 = *node;
	while ((tmp1)->next != NULL)
	{
		if (ft_strcmp((tmp1)->next->key, key))
		{
			(tmp1)->next = (tmp1)->next->next;
			return (node);
		}
		tmp1 = tmp1->next;
	}
	return (node);
}

int	ft_unset_write(char *str)
{
	int	check;

	write(2, "mminishell: unset: `", 20);
	write(2, str, ft_strlen_b(str));
	write(2, "': not a valid identifier\n", 27);
	check = 1;
	ft_status(1, 1);
	return (check);
}

void	ft_unset(char **cmd, t_env **cnev, t_env **exp)
{
	char	**dptr;
	int		i;
	int		j;
	int		check;

	i = 0;
	check = 0;
	while (cmd[i])
	{
		dptr = ft_split(cmd[i], ' ');
		j = 0;
		while (dptr[j])
		{
			if (check == 1 || !is_alpha_2(dptr[j]))
				check = ft_unset_write(dptr[j]);
			if (!check)
			{
				cnev = fun(cnev, dptr[j]);
				exp = fun(exp, dptr[j]);
				ft_status(0, 1);
			}
			j++;
		}
		i++;
	}
}
