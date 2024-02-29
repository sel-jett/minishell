#include "../includes/minishell.h"

void	execute(t_node_arbre	*tree, t_env	*env)
{

	// ft_env(env);
	if (!tree)
		return ;
	if (tree->mode == 0)
		ft_execute_cmd(tree, env);
	else if (tree->mode == 5)
		ft_execute_pipe(tree, env);
	// else if (tree->mode == 6)
	// 	ft_execute_and(tree);
	// else if (tree->mode == 7)
	// 	ft_execute_or(tree);
	// else if (tree->mode == 8)
	// 	ft_execute_expr(tree);
	// else if (tree->mode == 9)
	// 	ft_execute_redir_in(tree);
	// else if (tree->mode == 10)
	// 	ft_execute_redir_out(tree);
	// else if (tree->mode == 11)
	// 	ft_execute_redir_append(tree);
	// else if (tree->mode == 12)
	// 	ft_execute_heredoc(tree);
	// else if (tree->mode == 13)
	// 	ft_execute_double_q(tree);
	// else if (tree->mode == 14)
	// 	ft_execute_single_q(tree);
	// else if (tree->mode == 15)
	// 	ft_execute_dollar(tree);
	// else if (tree->mode == 16)
	// 	ft_execute_parenthese(tree);
}
