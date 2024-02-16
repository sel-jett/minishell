#include "../../includes/minishell.h"

static void    fun_1(char *str, t_list *list, int *i)
{
	int     len;
	char    *s;
	int     j;

	(1 == 1) && (len  = 1, *i += 1,j = -1);
	while (str[len] && str[len] != '"')
		len++;
	if (str[len] != '"')
		exit(write(2,"ERROR\n",7));
	s = my_malloc (len * sizeof(char),1);
	if (!s)
		exit(1);
	while (++j < (len - 1))
		s[j] = str[j + 1];
	s[j] = '\0';
	add_back(list, c_node(s, list->tail, TOKEN_Double_Q));
	*i += len;
	
}

static void    fun_2(char *str, t_list *list,int *i)
{
	int     len;
	char    *s;
	int     j;

	(1 == 1) && (len  = 1, *i += 1, j = -1);
	while (str[len] && str[len] != '\'')
		len++;
	if (str[len] != '\'')
		exit(write(2, "ERROR\n", 7));
	s = my_malloc (len * sizeof(char),1);
	if (!s)
		exit(1);
	while (++j < (len - 1))
		s[j] = str[j + 1];
	s[j] = '\0';
	add_back(list, c_node(s, list->tail, TOKEN_Single_Q));
	*i += len;
}

void    plant_1(char *str,t_list *list,int *i)
{
	if (*str == '"')
		fun_1(str, list, i);
	else if (*str == '\'')
		fun_2(str, list, i);
}