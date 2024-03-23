/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:27:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/23 09:09:30 by amel-has         ###   ########.fr       */
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

int	is_alpha_3(char c)
{
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| c == '_' || (c >= '0' && c <= '9')))
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

t_env* delfirst(t_env **node) {
    if (*node == NULL)
        return NULL;
    *node = (*node)->next;
    return *node;
}

void fun(t_env ***node, char *key)
{    
    if (ft_strcmp((**node)->key, key))
    {
        **node = delfirst(*node);
        return ;
    }
    t_env **tmp1 = *node;
    while ((*tmp1)->next != NULL)
    {
        if (ft_strcmp((*tmp1)->next->key, key)) {
            (*tmp1)->next = (*tmp1)->next->next;
            return;
        }
        (*tmp1) = (*tmp1)->next;
    } 
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
			{
				write(2, "mminishell: unset: `", 20);
				write(2, dptr[j], ft_strlen_b(dptr[j]));
				write(2, "': not a valid identifier\n", 27);
				check = 1;
				ft_status(1, 1);
			}
			if (!check)
			{
				fun(&cnev, dptr[j]);
				fun(&exp, dptr[j]);
				ft_status(0, 1);
			}
			j++;
		}
		i++;
	}
}
