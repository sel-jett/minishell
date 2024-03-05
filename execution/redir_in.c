#include "../includes/minishell.h"

void	ft_execute_redir_in(t_node_arbre *tree, t_env *env, t_env *exp)
{
	int		fd;
	int		status;
	pid_t	pid;

	tree->mode = TOKEN_EXPR;
	fd = open(tree->list_redir->tail->value, O_RDONLY);
	if (fd == -1)
	{
		perror("open error");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid == 0)
	{
		dup2(fd, 0);
		close(fd);
		execute(tree, env, exp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_status(status, 1);
}
