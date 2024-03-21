/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:12:36 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/21 03:37:07 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_node_arbre *tree, t_env *env, t_env *exp)
{
	
	// while (tree->right->list->top)
	// {
	// 	// dprintf(2, "[%s]\n", tree->right->list->top->value);
	// 	dprintf(2, "[%s][%d]\n", tree->right->list->top->value, tree->right->list->top->flag_space);
	// 	tree->right->list->top = tree->right->list->top->next;
	// }
	// exit(0);
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
