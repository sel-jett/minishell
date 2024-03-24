/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:04:56 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/24 07:10:39 by amel-has         ###   ########.fr       */
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
