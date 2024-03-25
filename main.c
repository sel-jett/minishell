/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:12:48 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 17:11:14 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int x = 0;

void	handler_signel(int signal, siginfo_t *siginfo, void *vd)
{
	(void)vd;
	(void)siginfo;
	if (signal == SIGINT)
	{
		if (x == 0)
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

int	main(int ac, char **av, char **envp)
{
	t_var var;

	(1) && (var.sa.sa_flags = SA_SIGINFO, var.list = NULL);
	(1) && (var.sa.sa_sigaction = handler_signel, var.nlist = NULL);
	handel_signel_(var.sa);
	(1) && (var.env = ft_env_parser(envp), var.exp = ft_env_parser(envp));
	if (!var.env)
	{
		ft_lstadd_back(&var.env, env_new("PATH=/Users/sel-jett/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", var.env));
		ft_lstadd_back(&var.env, env_new("SHLVL=1", var.env));
		ft_lstadd_back(&var.env, env_new("_=/usr/bin/env", var.env));
		ft_lstadd_back(&var.env, env_new(ft_strjoin("PWD=", getcwd(0, 0)), var.env));
		ft_lstadd_back(&var.exp, env_new("PATH=/Users/sel-jett/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", var.exp));
		ft_lstadd_back(&var.exp, env_new("SHLVL=1", var.exp));
		ft_lstadd_back(&var.exp, env_new(ft_strjoin("PWD=", getcwd(0, 0)), var.exp));
	}
	ft_lstadd_back(&var.exp, env_new("OLDPWD", var.exp));
	(void)ac;
	(void)av;
	while (1)
	{
		(1) && (var.n = 0, var.index = 0, var.list = c_list());
		if (!var.list)
			(1) && (printf("ERROR CREAT LISTE\n") && (var.index = 1));
		if (!var.index)
		{
			var.list->str = 0;
			var.list->str = readline("minishell > ");
			ctrld(var.list->str, &var.index);
			if (!var.index)
			{
				add_history(var.list->str);
				read_parse(&var.index, var.list, var.exp, &var.n);
				add_redir_parse(var.list, &var.index, var.n, &var.nlist);
				if (x == 10)
					x = 0;
				if (!var.index)
				{
					var.arbre = c_arbre();
					if (!var.arbre)
						var.index = 1;
				}
				if (!var.index)
				{
					if (!plant_6(var.nlist->top, &var.arbre->racine))
						(1 == 1) && (printf("ERROR7\n"), var.index = 1);
				}
				if (!var.index)
				{
					execute(var.arbre->racine, var.env, var.exp);
					sigaction(SIGINT, &var.sa, NULL);
					sigaction(SIGQUIT, &var.sa, NULL);
					x = 0;
					free(var.list->str);
				}
			}
		}
	}
	my_malloc(0, 0);
	return (0);
}
