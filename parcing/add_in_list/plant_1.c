#include "../../includes/minishell.h"

static int    fun_1(char *str, t_list *list, int *i)
{
	int     len;
	char    *s;
	int     j;
	t_node	*node;

	(1 == 1) && (len  = 1, *i += 1,j = -1,node = 0);
	while (str[len] && str[len] != '"')
		len++;
	if (str[len] != '"')
		return (0);
	s = my_malloc (len * sizeof(char),1);
	if (!s)
		return (0);
	while (++j < (len - 1))
		s[j] = str[j + 1];
	s[j] = '\0';
	node = c_node(s, list->tail, TOKEN_Double_Q);
	if (!node)
		return (0);
	add_back(list, node);
	*i += len;
	return (1);
}

static int    fun_2(char *str, t_list *list,int *i)
{
	int     len;
	char    *s;
	int     j;
	t_node  *node;

	(1 == 1) && (len  = 1, *i += 1, j = -1,node = 0);
	while (str[len] && str[len] != '\'')
		len++;
	if (str[len] != '\'')
		return (0);
	s = my_malloc (len * sizeof(char),1);
	if (!s)
		return (0);
	while (++j < (len - 1))
		s[j] = str[j + 1];
	s[j] = '\0';
	node = c_node(s, list->tail, TOKEN_Single_Q);
	if (!node)
		return (0);
	add_back(list, node);
	*i += len;
	return (1);
}

int    plant_1(char *str,t_list *list,int *i)
{
	if (*str == '"')
	{
		if(!fun_1(str, list, i))
			return (0);
	}
	else if (*str == '\'')
	{
		if (!fun_2(str, list, i))
			return (0);
	}
	return (1);
}