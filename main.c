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

// int	plant_0(t_list *list , char *str, int *i)
// {
// 	int		len = 0;
// 	char 	*s = 0;

// 	while (str[len]  && str[len] != ')')
// 		len++;
// 	s = my_malloc(sizeof(char) * (len + 1),1);
// 	if (!s)
// 		return (0);
// 	len = 0;
// 	while (str[len]  && str[len] != ')')
// 	{
// 		s[len] = str[len];
// 		len++;
// 	}
// 	s[len] ='\0';
// 	add_back(list, c_node(s,list->tail,TOKEN_PARENTHESE));
// }

int	main(void)
{
	t_list  *list;
	int     i;
	int		count_prth;
	char    *str;

	(1== 1) && (str = NULL,count_prth = 0);
	while (1)
	{
		list = c_list();
		i = 0;
		str = readline("minishell > ");
		add_history(str);
		while (str && str[i])
		{
			
			if (str[i] == '(' || str[i] == ')')
			{
				if (!add_one(&str[i], list, &i, TOKEN_PARENTHESE)){
					printf("ERROR\n");
					break;
				}
			}
			else if (str[i] == ' ')
			{
				if (!spaces(&str[i], list, &i))
				{
					printf("ERROR\n");
					break;
				}
			}
			else if ((str[i] == '"' || str[i] == '\''))
			{
				if (!plant_1(&str[i], list, &i))
				{
					printf("ERROR\n");
					break;
				}
			}
			else if (check(str[i]))
			{
				if (!plant_2(&str[i], list, &i))
				{
					printf("ERROR\n");
					break;
				}
			}
			else if (!check(str[i]))
			{
				if (!plant_3(&str[i], list, &i))
				{
					printf("ERROR\n");
					break;
				}
			}
		}
		if (!plant_4(list))
		{
			printf("ERROR\n");
			break;
		};
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