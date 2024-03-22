/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:12:36 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 01:15:14 by sel-jett         ###   ########.fr       */
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
