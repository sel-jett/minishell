#include "../../includes/minishell.h"

int	check(int c)
{
	if (c && c != '|' && c != '&' && c !=
		'<' && c != '>' && c != '\'' && c != '&' && c != '"' && c != ' ')
		return (1);
	return (0);
}

int		plant_2(char *str, t_list   *list, int *i)
{
	int     len;
	char    *s;
	t_node	*node;

	len  = 0;
	s = NULL;node = NULL;
	while (check(str[len]))
		len++;
	s = my_malloc(sizeof(char) * (len + 1), 1);
	if (!s)
		return(0);
	(1 == 1) && (*i += len, len = -1);
	while (check(str[++len]))
		s[len] = str[len];
	s[len] = '\0';
	node = c_node(s, list->tail, TOKEN_EXPR);
	if (!node)
		return (0);
	add_back(list, node);
	return (1);
}