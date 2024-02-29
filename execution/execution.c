#include "../includes/minishell.h"

void	execute(t_node_arbre	*tree, t_env	*env)
{

	// // ft_env(env);
	// puts("//////////////////////////");
	// // puts(tree->value);
	// fprintf(stderr, "value: %s\n", tree->value);
	// puts("//////////////////////////");
	if (!tree)
		return ;
	if (tree->mode == 0)
		ft_execute_cmd(tree, &env);
	else if (tree->mode == TOKEN_PIPE)
		ft_execute_pipe(tree, env);
	else if (tree->mode == TOKEN_AND)
		ft_execute_and(tree, env);
	else if (tree->mode == TOKEN_OR)
		ft_execute_or(tree, env);
	else if (tree->mode == TOKEN_PARENTHESE)
		ft_execute_subshell(tree, env);
	else if (tree->mode == TOKEN_REDIR_OUT)
		ft_execute_redir_out(tree, env);
	else if (tree->mode == TOKEN_REDIR_IN)
		ft_execute_redir_in(tree, env);
}
