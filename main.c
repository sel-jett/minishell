#include "includes/minishell.h"

plant_5(t_node *node)
{
	
}

int	main(void)
{
	t_list  *list;
	int     i;
	int		index;
	t_arbre			*arbre;

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
					arbre = c_arbre();
						if (!arbre)
							return (0);
				plant_5(list->top);
				if (!index)
					if (!plant_6(list->top, &arbre->racine))
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
