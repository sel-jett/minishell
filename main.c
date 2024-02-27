#include "includes/minishell.h"

int	plant_5(t_node	*tmp, t_list *list)
{
	t_node	*node;

	node = NULL;
	if (!list)
		return (0);
	while (tmp)
	{
		if (tmp->mode != TOKEN_SPACE)
		{
			node = c_cpynode(tmp,list->tail,list);
			if (!node)
				return (0);
			add_back(list, node);
		}
		if (tmp->next && tmp->next->mode == TOKEN_SPACE)
				node->flag_space = 1;
		if (!tmp->next)
			node->flag_space = 1;
		if (tmp->list_arg && tmp->list_arg->top)
					node->flag_expend = 1;
		tmp = tmp->next;
	}
	tmp = list->top;
	while (tmp)
	{
		if (tmp->mode == TOKEN_Double_Q || tmp->mode == TOKEN_Single_Q)
		{
			if (tmp->mode == TOKEN_Double_Q)
				if (tmp->list_arg && tmp->list_arg->top)
					node->flag_expend = 1;
			tmp->mode = TOKEN_EXPR;
		}
		tmp = tmp->next;
	}
	
	return	(1);
}

void	handler_signel(int signal, siginfo_t *siginfo, void *vd)
{
	(void)vd;
	(void)siginfo;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}

int	main(void)
{
	t_list  *list;
	int     i;
	int		index;
	t_arbre			*arbre;
	t_list	*nlist;

	(1== 1) && (list = NULL);
	struct sigaction	sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_signel;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	rl_catch_signals = 0;
	while (1)
	{
		(1 == 1) && (index = 0, i = 0, list = c_list(), list->str = 0);
		if (!list)
			(1 == 1) && (printf("ERROR1\n"), index = 1);
		if (!index)
		{
			list->str = readline("minishell > ");
			if (!list->str)
				exit(0);
			if (is_empty(list->str))
				index = 1;
			if (!index)
			{
				add_history(list->str);
				while (list->str[i])
					if (!plants(list, &i))
					{
						index = 1;
						break ;
					}
				if (!index)
					if (!plant_4(list))
						(1 == 1) && (printf("ERROR7\n"), index = 1);
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
						(1 == 1) && (printf("ERROR8\n"), index = 1);
				}
				if (!index)
				{
					// print_tree(arbre->racine, 0);
					my_malloc(0, 0);
				}
			}
		}
	}
	return (0);
}
