#include "../../includes/minishell.h"

int		spaces(char *str, t_list   *list, int *i)
{
	char	*s;
    int		len;
	t_node	*node;

    len = 0;
	s = my_malloc(sizeof(char) * 2, 1);
	if (!s)
		return(0);
	(1 == 1) && (s[0] = ' ', s[1] = '\0');
	node = c_node(s, list->tail, TOKEN_SPACE);
	if (!node)
		return (0);
	add_back(list, node);
	while (str[len] && str[len] == ' ')
        len++;
    (*i) += len;
	return (1);
}