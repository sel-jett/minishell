/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:12:44 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/18 20:19:59 by sel-jett         ###   ########.fr       */
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
	exit(0);
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
	exit(0);
}

static void	close_pipe(pid_t pid[2], int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

void	ft_execute_pipe(t_node_arbre *tree, t_env *e, t_env *exp)
{
	int		fd[2];
	pid_t	pid[2];

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
		ft_execute_left(tree, fd, e, exp);
	pid[1] = fork();
	if (pid[1] == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid[1] == 0)
		ft_execute_right(tree, fd, e, exp);
	close_pipe(pid, fd);
}
