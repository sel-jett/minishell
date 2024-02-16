#include "../../includes/minishell.h"

int	check(int c)
{
	if (c && c != '|' && c != '&' && c !=
		'<' && c != '>' && c != '\'' && c != '&' && c != '"' && c != ' ')
		return (1);
	return (0);
}

void    plant_2(char *str, t_list   *list, int *i)
{
	int     len;
	char    *s;

	len  = 0;
	s = NULL;
	while (check(str[len]))
		len++;
	s = my_malloc(sizeof(char) * (len + 1), 1);
	if (!s)
		exit(0);
	(1 == 1) && (*i += len, len = -1);
	while (check(str[++len]))
		s[len] = str[len];
	s[len] = '\0';
	add_back(list,c_node(s, list->tail, TOKEN_EXPR));
}