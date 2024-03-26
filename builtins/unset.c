/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:27:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 06:23:22 by sel-jett         ###   ########.fr       */
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
	if (!*c)
		return (0);
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
	int		i;
	int		check;
	char	**tmp;
	int		j, k, l;

	(1) && (j = 0, k = 0, l = 0);
	i = 0;
	check = 0;
	tmp = array_31(ft_31_spliter(cmd, j, k, l));
	while (tmp[i])
	{
			if (check == 1 || !is_alpha_2(tmp[i]))
			{
				if (cmd[i] && ft_strlen_b(cmd[i]) > 0 && cmd[i][ft_strlen_b(cmd[i]) - 1] != -31)
					check = ft_unset_write(tmp[i]);
			}
			if (!check)
			{
				cnev = fun(cnev, tmp[i]);
				exp = fun(exp, tmp[i]);
				ft_status(0, 1);
			}
			check = 0;
		i++;
	}
}
