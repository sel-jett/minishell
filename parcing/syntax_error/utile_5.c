/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:49:46 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 08:01:08 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	affichage(int n)
{
	printf("minishell:syntax error near unexpected token %d\n", n);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\v' && str[i] != '\f' && str[i] != '\v')
			return (0);
		i++;
	}
	return (1);
}

int	ft_status(int status, bool mode)
{
	static int	stat;

	if (mode == 1)
		stat = status;
	return (stat);
}

void	check_wilc(t_node *node)
{
	int	i;

	i = 0;
	while (node->value[i] && node->mode == TOKEN_EXPR)
	{
		if (node->value[i] == '*')
			node->flag_wilc = 1;
		i++;
	}
}

int	add_args(t_nlist *list, char *str, int *i)
{
	int		len;
	char	*s;
	t_nnode	*node;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && str[len] != ' ' && str[len] != '$')
		len++;
	s = my_malloc(sizeof(char) * (len + 1), 1);
	if (!s)
		return (0);
	len = 0;
	while (str && str[len] && str[len] != ' ' && str[len] != '$')
	{
		s[len] = str[len];
		len++;
	}
	s[len] = '\0';
	*i += len;
	node = c_nnode(c_node(s, NULL, -1, NULL));
	if (!node)
		return (0);
	add_nback(list, node);
	return (1);
}
