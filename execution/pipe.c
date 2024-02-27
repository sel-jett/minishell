#include "../includes/minishell.h"

void	ft_execute_pipe(t_node_arbre *tree)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
	{
		perror("pipe error");
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
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execute(tree->left);
		exit(0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execute(tree->right);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	while (waitpid(-1, &status, 0) > 0);
}
