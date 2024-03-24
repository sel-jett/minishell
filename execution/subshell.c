/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:29:50 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/24 12:23:20 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_subshell(t_node_arbre *tree, t_env *e, t_env *exp)
{
	int			pid;
	int			status;
	extern int	x;

	x = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid == 0)
	{
		// dprintf(2, "pid = %s\n", tree->arbre->racine->left->list_redir->top->value);
		// exit(1);
		execute(tree->arbre->racine, e, exp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_status(status, 1);
}
