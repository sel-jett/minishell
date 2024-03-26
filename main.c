/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:12:48 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/26 21:51:09 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handler_signel(int signal, siginfo_t *siginfo, void *vd)
{
	(void)vd;
	(void)siginfo;
	if (signal == SIGINT)
	{
		if (g_x == 0)
		{
			ft_status(1, 1);
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			ft_status(1, 1);
			printf("\n");
		}
	}
}

void	exec_execute(t_var var)
{
	execute(var.arbre->racine, var.env, var.exp);
	sigaction(SIGINT, &var.sa, NULL);
	sigaction(SIGQUIT, &var.sa, NULL);
	g_x = 0;
	free(var.list->str);
}

void	init_var(t_var *var)
{
	var->sa.sa_flags = SA_SIGINFO;
	var->list = NULL;
	var->arbre = NULL;
	var->sa.sa_sigaction = handler_signel;
	var->nlist = NULL;
	var->nlist = NULL;
}

void	funs(t_var *var)
{
	add_history(var->list->str);
	read_parse(&var->index, var->list, var->exp, &var->n);
	add_redir_parse(var->list, &var->index, var->n, &var->nlist);
	(g_x == 10) && (g_x = 0);
	create_tree(var);
	if (!var->index)
	{
		if (!plant_6(var->nlist->top, &var->arbre->racine))
			(1 == 1) && (printf("ERROR7\n"), var->index = 1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_var	var;

	init_var(&var);
	handel_signel_(var.sa);
	env_init(&var, envp);
	(1) && ((void)ac, (void)av, 0);
	while (1)
	{
		(1) && (var.n = 0, var.index = 0, var.list = c_list());
		if (!var.list)
			(1) && (printf("ERROR CREATING\n"), my_malloc(0, 2), exit(1), 0);
		if (!var.index)
		{
			(1) && (var.list->str = 0, var.list->str = readline("minishell> "));
			ctrld(var.list->str, &var.index);
			if (!var.index)
			{
				funs(&var);
				if (!var.index)
					exec_execute(var);
			}
		}
	}
	return (my_malloc(0, 0), 0);
}
