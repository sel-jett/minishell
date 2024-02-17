/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:07:15 by amel-has          #+#    #+#             */
/*   Updated: 2024/02/17 17:21:26 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	spaces(t_list *list, int *i)
{
	char	*s;
	int		len;
	t_node	*node;

	len = 0;
	s = my_malloc(sizeof(char) * 2, 1);
	if (!s)
		return (0);
	(1 == 1) && (s[0] = ' ', s[1] = '\0');
	node = c_node(s, list->tail, TOKEN_SPACE);
	if (!node)
		return (0);
	add_back(list, node);
	while (list->str[*i + len] && list->str[*i + len] == ' ')
		len++;
	(*i) += len;
	return (1);
}
