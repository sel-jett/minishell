/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:12:44 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/23 07:22:13 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_execute_left(t_node_arbre *t, int f[2], t_env *e, t_env *d)
{
	if (dup2(f[1], 1) == -1)
	{
		perror("dup2 error");
		exit(1);
	}
	close(f[0]);
	close(f[1]);
	execute(t->left, e, d);
	exit(127);
}

static void	ft_execute_right(t_node_arbre *t, int f[2], t_env *e, t_env *d)
{
	if (dup2(f[0], 0) == -1)
	{
		perror("dup2 error");
		exit(1);
	}
	close(f[0]);
	close(f[1]);
	execute(t->right, e, d);
	exit(127);
}

static void	close_pipe(pid_t pid[2], int fd[2])
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
        ft_status(WEXITSTATUS(status), 1);
    else if (WIFSIGNALED(status))
    {
        ft_status(128 + WTERMSIG(status), 1);
        if (WTERMSIG(status) == SIGQUIT)
            dprintf(2, "Quit: %d\n", SIGQUIT);
    }
	// ft_status((status % 255), 1);
}

void	ft_execute_pipe(t_node_arbre *tree, t_env *e, t_env *exp)
{
	int			fd[2];
	pid_t		pid[2];
	extern int	x;

	if (pipe(fd) == -1)
	{
		perror("pipe error");
		return ;
	}
	x = 1;
	pid[0] = fork();
	if (pid[0] == -1)
	{
		perror("fork error");
		return ;
	}
	(pid[0] == 0) && (ft_execute_left(tree, fd, e, exp), exit(ft_status(0, 0)), 0);
	pid[1] = fork();
	if (pid[1] == -1)
	{
		perror("fork error");
		return ;
	}
	(pid[1] == 0) && (ft_execute_right(tree, fd, e, exp), exit(ft_status(0, 0)), 0);
	close_pipe(pid, fd);
}
