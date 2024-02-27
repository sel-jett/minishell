#include "../includes/minishell.h"

void	ft_execute_redir_in(t_node_arbre *tree)
{
	int		fd;
	int		status;
	pid_t	pid;

	fd = open(tree->left->value, O_RDONLY);
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
		execute(tree->right);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}
