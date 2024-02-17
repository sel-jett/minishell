#include "../../includes/minishell.h"

static  int	add_two(char *str, t_list   *list, int *i ,int mode)
{
	char	*s;
	int		j;
	t_node	*node;

	(1 == 1) && (j = -1, s = 0,node = 0);
	s = my_malloc(sizeof(char) * 3, 1);
	if (!s)
		return (0);
	while (++j < 2)
		s[j] = str[0];
	s[j] = '\0';
	node = c_node(s, list->tail, mode);
	if (!node)
		return (0);
	add_back(list, node);
	*i += 2;
	return (1);
}

int		add_one(char *str, t_list   *list, int *i ,int mode)
{
	char	*s;
	t_node	*node;

	(1 == 1) && (s = 0,node = NULL);
	s = my_malloc(sizeof(char) * 2, 1);
	if (!s)
		return(0);
	(1 == 1) && (s[0] = str[0], s[1] = '\0');
	node = c_node(s, list->tail, mode);
	if (!node)
		return (0);
	add_back(list, node);
	(*i)++;
	return (1);
}

int	plant_3(char *str, t_list   *list, int *i)
{
	int index = 0;
	if (!str)
		return (0);
	if (str[0] == '<')
	{
		if (str[1] && str[1] == '<')
		{
			if (!add_two(str, list, i, TOKEN_REDIR_IN))
				return (0);
		}
		else
			if (!add_one(str, list, i, TOKEN_HEREDOC))
				return (0);
	}
	else if (str[0] == '|')
	{
		if (str[1]){
			if (str[1]  == '|')
			{
				if (!add_two(str, list, i, TOKEN_OR))
					return (0);
				index = 1;
			}}
		if (index == 0)
			if (!add_one(str, list, i, TOKEN_PIPE))
				return (0);
	}
	else if (str[0] == '>')
	{
		if (str[1] && str[1] == '>')
		{
			if (!add_two(str, list, i, TOKEN_REDIR_APPEND))
				return (0);
		}
		else
			if (!add_one(str, list, i, TOKEN_REDIR_OUT))
				return (0);
	}
	else if(str[0] == '&')
	{
		if (str[1] && str[1] == '&')
		{
			if (!add_two(str, list, i, TOKEN_AND))
				return (0);
		}
		else
			return (0);
	}
	return (1);
}