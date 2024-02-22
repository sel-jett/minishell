#include "includes/minishell.h"

void affiche(t_list *list)
{
		t_node *tmp = list->top;
		while(tmp)
		{
		printf("[prev : %p]            [me :[%p] | val : [%s] | mode : [%d]]             [next : %p]\n",tmp->prev, tmp, tmp->value, tmp->mode, tmp->next);
		if (tmp->value[0] && tmp->mode == 11)
		{
			t_node_arg *tmp1 = tmp->list_arg->top;
			while(tmp1)
			{
				printf("\nthis is ---------- >[%s]\n",tmp1->value);
				tmp1 = tmp1->next;
			}
		}
		if (tmp->mode == TOKEN_REDIR_APPEND || tmp->mode == TOKEN_REDIR_IN || tmp->mode == TOKEN_REDIR_OUT || tmp->mode == TOKEN_HEREDOC)
		{
			t_node_redir *tmp2;

			tmp2 = tmp->list_redir->top;
			printf("-------------------------------------\n");
			while (tmp2)
			{
				printf("-------->%s\n",tmp2->value);
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
		}
}

int	main(void)
{
	t_list  *list;
	int     i;
	int		index;

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
						break;
				if (!plant_4(list))
					(1 == 1) && (printf("ERROR7\n"), index = 1);
				if (!plant_5(list))
					(1 == 1) && (printf("ERROR7\n"), index = 1);
				if (!index)
				{
					// affiche(list);
					my_malloc(0, 0);
				}
			}
		}
	}
	return (0);
}
