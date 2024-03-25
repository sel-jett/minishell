/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:04:56 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 17:13:59 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	igno_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	def_sig(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

bool	is_redir(t_node *tmp)
{
	if (tmp->mode == TOKEN_HEREDOC || tmp->mode == TOKEN_REDIR_IN
		|| tmp->mode == TOKEN_REDIR_OUT || tmp->mode == TOKEN_REDIR_APPEND)
		return (1);
	return (0);
}

void	add_redir_parse(t_list *list, int *index, int n, t_list **nlist)
{
	t_node	*i_node;

	i_node = list->top;
	if (!*index)
	{
		while (i_node && !*index)
		{
			if (is_redir(i_node))
				if (!add_list_redir(i_node))
					*index = 1;
			i_node = i_node->next;
		}
	}
	if (n == 1)
		*index = 1;
	if (!*index)
	{
		*nlist = c_list();
		if (!*nlist)
			*index = 1;
		if (!plant_5(list->top, *nlist))
			*index = 1;
	}
}

void	ctrld(char *str, int *index)
{
	if (!str)
	{
		printf("exit\n");
		exit(0);
	}
	if (!*index && is_empty(str))
		*index = 1;
}
