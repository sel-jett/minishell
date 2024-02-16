#include "includes/minishell.h"

int	main(void)
{
	t_list  *list;
	int     i;
	char    *str;

	str = NULL;
	while (1)
	{
		list = c_list();
		i = 0;
		str = readline("minishell > ");
		add_history(str);
		while (str && str[i])
		{
			if (str[i] && str[i] == ' ')
				spaces(&str[i], list, &i);
			else if (str[i] && (str[i] == '"' || str[i] == '\''))
				plant_1(&str[i], list, &i);
			else if (str[i] && check(str[i]))
				plant_2(&str[i], list, &i);
			else if (str[i] && !check(str[i]))
				plant_3(&str[i], list, &i);
		}
		plant_4(list);
		t_node *tmp = list->top;
		while(tmp)
		{
			printf("[prev : %p] |[me :%p | val : %s] [next : %p]\n",tmp->prev,tmp,tmp->value,tmp->next);
			if (tmp->mode == 11){
				t_node_arg *tmp1 = tmp->list_arg->top;
				while(tmp1)
				{
					printf("\nthis is ---------- >[%s]\n",tmp1->value);
					tmp1 = tmp1->next;
				}
			}
			tmp = tmp->next;
		}
		my_malloc(0,0);
	}
	return (0);
}