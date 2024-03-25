/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:12:48 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 01:04:07 by amel-has         ###   ########.fr       */
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

int main(int ac, char **av, char **envp)
{
	t_list				*list;
	int					i;
	int					index;
	t_arbre				*arbre;
	t_list				*nlist;
	t_env				*env;
	t_env				*exp;
	struct sigaction	sa;
	int					n;

	list = NULL;
	rl_catch_signals = 0;
	nlist = NULL;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_signel;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	env = ft_env_parser(envp);
	exp = ft_env_parser(envp);
	if (!env)
	{
		ft_lstadd_back(&env, env_new("PATH=/Users/sel-jett/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", env));
		ft_lstadd_back(&env, env_new("SHLVL=1", env));
		ft_lstadd_back(&env, env_new("_=/usr/bin/env", env));
		ft_lstadd_back(&env, env_new(ft_strjoin("PWD=", getcwd(0, 0)), env));
		ft_lstadd_back(&exp, env_new("PATH=/Users/sel-jett/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", exp));
		ft_lstadd_back(&exp, env_new("SHLVL=1", exp));
		ft_lstadd_back(&exp, env_new(ft_strjoin("PWD=", getcwd(0, 0)), exp));
	}
	ft_lstadd_back(&exp, env_new("OLDPWD", exp));
	(void)ac;
	(void)av;
	while (1)
	{
		(1) && (n = 0, index = 0, i = 0, list = c_list(), list->str = 0);
		if (!list)
			(1) && (printf("ERROR CREAT LISTE\n") && (index = 1));
		if (!index)
		{
			if (x == 0)
			list->str = readline("minishell > ");
			if (!list->str)
			{
				printf("exit\n");
				exit(0);
			}
			if (is_empty(list->str))
				index = 1;
			if (!index)
			{
				add_history(list->str);
				while (list->str[i])
				{
					if (!plants(list, &i))
					{
						index = 1;
						break;
					}
				}
				if (!index)
					if (!plant_4(list, exp, &n))
						index = 1;
				if (!index){
				t_node *i_node = list->top;
				while (i_node)
				{
					if (is_redir(i_node))
					{
						if (!add_list_redir(i_node))
							return (index = 1, 0);	
					}
					i_node = i_node->next;
				}
				}
				if (n == 1)
					index = 1;
				if (!index)
				{
					nlist = c_list();
					if (!nlist)
						index = 1;
					if (!plant_5(list->top, nlist))
						index = 1;
				}
				if (!index)
				{
					arbre = c_arbre();
					if (!arbre)
						index = 1;
				}
				if (!index)
				{
					if (!plant_6(nlist->top, &arbre->racine))
						(1 == 1) && (printf("ERROR7\n"), index = 1);
				}
				if (!index)
				{
					execute(arbre->racine, env, exp);
					sigaction(SIGINT, &sa, NULL);
					sigaction(SIGQUIT, &sa, NULL);
					x = 0;
					free(list->str);
				}
			}
		}
	}
	my_malloc(0, 0);
	return (0);
}
