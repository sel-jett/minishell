#include "../includes/minishell.h"

void	ft_execute_redir_out(t_node_arbre *tree, t_env	*env)
{
	int		fd;
	int		status;
	pid_t	pid;

	fd = open(tree->list_redir->tail->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
		dup2(fd, 1);
		close(fd);
		execute(tree, env);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_status(status, 1);
}
