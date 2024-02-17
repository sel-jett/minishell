#include "includes/minishell.h"

bool	check_entre_parentheses(char *str)
{
	int i = 0;
	while(str[i] && str[i] != ')')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void affiche(t_list *list)
{
		t_node *tmp = list->top;
		while(tmp)
		{
		printf("        [me :%p | val : %s ]            [next : %p]\n",tmp,tmp->value,tmp->next);
		if (tmp->mode == 11)
		{
			t_node_arg *tmp1 = tmp->list_arg->top;
			while(tmp1)
			{
				printf("\nthis is ---------- >[%s]\n",tmp1->value);
				tmp1 = tmp1->next;
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
		(1 == 1) && (index = 0, i = 0, list = c_list(),list->str = NULL);
		if (!list)
		{
			printf("ERROR1\n");index = 1;
			break;
		}
		list->str = readline("minishell > ");
		if (!list->str)
			index = 1;
		add_history(list->str);
		if (index == 0)
		{
			while (list->str[i])
				if (!plants(list, &i))
					break;
			if (!plant_4(list))
			{
				printf("ERROR7\n");
				index = 1;
			}
		}
		if (index == 0)
			affiche(list);
		my_malloc(0, 0);
	}
	return (0);
}