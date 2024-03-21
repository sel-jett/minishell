/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:49:28 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 09:01:27 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_herdoc_0(t_node *tmp)
{
	char		*file;
	t_nnode		*i_node;

	(1) && (file = 0, i_node = 0);
	if (tmp->mode == TOKEN_HEREDOC)
		tmp->mode = TOKEN_REDIR_IN;
	i_node = tmp->list_redir->top;
	while (i_node)
	{
		if (i_node->mode == TOKEN_HEREDOC)
		{
			if (!open_herdoc(i_node, &file))
				return (0);
			if (i_node->next)
				i_node->next->value = file;
			i_node->value = "<";
			i_node->mode = TOKEN_REDIR_IN;
		}
		i_node = i_node->next;
	}
	return (1);
}
