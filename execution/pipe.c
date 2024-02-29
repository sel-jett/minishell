#include "../includes/minishell.h"

void	ft_execute_pipe(t_node_arbre *tree, t_env *e)
{
	int		fd[2];
	pid_t	pid[2];
	// int		status;

	if (pipe(fd) == -1)
	{
		perror("pipe error");
		return ;
	}
	pid[0] = fork();
	if (pid[0] == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid[0] == 0)
	{
		// close(fd[0]);
		if (dup2(fd[1], 1) == -1)
		{
			perror("dup2 error");
			exit(1);
		}
		close(fd[0]);
		close(fd[1]);
		execute(tree->left, e);
		exit(0);
	}
	pid[1] = fork();
	if (pid[1] == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid[1] == 0)
	{
		if (dup2(fd[0], 0) == -1)
		{
			perror("dup2 error");
			exit(1);
		}
		close(fd[0]);
		close(fd[1]);
		execute(tree->right, e);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	// while (waitpid(-1, NULL, 0) > 0);
}
