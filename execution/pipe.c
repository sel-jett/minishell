/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:12:44 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 19:35:07 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_left(t_node_arbre *t, int f[2], t_env *e, t_env *d)
{
	if (dup2(f[1], 1) == -1)
	{
		perror("dup2 error");
		close(f[0]);
		close(f[1]);
	}
	close(f[0]);
	close(f[1]);
	execute(t->left, e, d);
	exit(ft_status(0, 0));
}

static void	ft_right(t_node_arbre *t, int f[2], t_env *e, t_env *d)
{
	if (dup2(f[0], 0) == -1)
	{
		perror("dup2 error");
		close(f[0]);
		close(f[1]);
		exit(1);
	}
	close(f[0]);
	close(f[1]);
	execute(t->right, e, d);
	exit(ft_status(0, 0));
}

static void	close_pipe(pid_t pid[2], int fd[2])
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status, 0);
	ft_status((status % 255), 1);
	waitpid(pid[1], &status, 0);
	ft_status((status % 255), 1);
}

void	ft_execute_pipe(t_node_arbre *tree, t_env *e, t_env *exp)
{
	int			fd[2];
	pid_t		pid[2];
	extern int	g_x;

	if (pipe(fd) == -1)
	{
		perror("pipe error");
		return ;
	}
	g_x = 1;
	pid[0] = fork();
	if (pid[0] == -1)
	{
		perror("fork error");
		return ;
	}
	(pid[0] == 0) && (ft_left(tree, fd, e, exp), exit(ft_status(0, 0)), 0);
	pid[1] = fork();
	if (pid[1] == -1)
	{
		perror("fork error");
		return ;
	}
	(pid[1] == 0) && (ft_right(tree, fd, e, exp), exit(ft_status(0, 0)), 0);
	close_pipe(pid, fd);
}
