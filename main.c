#include "includes/minishell.h"

int	plant_5(t_node	*tmp, t_list *list)
{
	t_node	*node;

	node = NULL;
	while (tmp)
	{
		if (tmp->mode != TOKEN_SPACE)
		{
			node = c_cpynode(tmp,list->tail);
			if (!node)
				return (0);
			add_back(list, node);
		}
		if (tmp->next && tmp->next->mode == TOKEN_SPACE)
				node->flag_space = 1;
		if (!tmp->next)
			node->flag_space = 1;
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

int	main(void)
{
	t_list  *list;
	int     i;
	int		index;
	t_arbre			*arbre;
	t_list	*nlist;

	(1== 1) && (list = NULL);
	while (1)
	{
		(1 == 1) && (index = 0, i = 0, list = c_list(), list->str = 0);
		if (!list)
			(1 == 1) && (printf("ERROR1\n"), index = 1);
		if (!index)
		{
			list->str = readline("minishell > ");
			if (!list->str || is_empty(list->str))
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
						return (0);
					if (!plant_5(list->top, nlist))
						index = 1;
					// affiche(nlist);
				}
				if (!index)
					arbre = c_arbre();
						if (!arbre)
							return (0);
				if (!index)
					if (!plant_6(nlist->top, &arbre->racine))
						(1 == 1) && (printf("ERROR7\n"), index = 1);
				if (!index)
				{
					print_tree(arbre->racine, 0);
					my_malloc(0, 0);
				}
			}
		}
	}
	return (0);
}
