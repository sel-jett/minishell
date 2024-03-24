/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:12:36 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 03:51:46 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_node_arbre *tree, t_env *env, t_env *exp)
{
	igno_sig();
	if (!tree)
		return ;
	if (tree->mode == 0)
		ft_execute_cmd(tree, &env, &exp);
	else if (tree->mode == TOKEN_PIPE)
		ft_execute_pipe(tree, env, exp);
	else if (tree->mode == TOKEN_AND)
		ft_execute_and(tree, env, exp);
	else if (tree->mode == TOKEN_OR)
		ft_execute_or(tree, env, exp);
	else if (tree->mode == TOKEN_PARENTHESE)
		ft_execute_subshell(tree, env, exp);
	else if (tree->mode == TOKEN_REDIR_OUT)
		ft_execute_redir_out(tree, env, exp);
	else if (tree->mode == TOKEN_REDIR_IN)
		ft_execute_redir_out(tree, env, exp);
	else if (tree->mode == TOKEN_REDIR_APPEND)
		ft_execute_redir_out(tree, env, exp);
}
