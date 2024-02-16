#include "../../includes/minishell.h"

static  void	add_two(char *str, t_list   *list, int *i ,int mode)
{
	char	*s;
	int		j;

	(1 == 1) && (j = -1, s = NULL);
	s = my_malloc(sizeof(char) * 3, 1);
	if (!s)
		exit(0);
	while (++j < 2)
		s[j] = str[0];
	s[j] = '\0';
	add_back(list, c_node(s, list->tail, mode));
	*i +=  2;
}

static void		add_one(char *str, t_list   *list, int *i ,int mode)
{
	char	*s;

	s = NULL;
	s = my_malloc(sizeof(char) * 2, 1);
	if (!s)
		exit(0);
	(1 == 1) && (s[0] = str[0], s[1] = '\0');
	add_back(list,c_node(s, list->tail, mode));
	(*i)++;
}

void	plant_3(char *str, t_list   *list, int *i)
{
	int index = 0;
	if (!str)
		return ;
	if (str[0] == '<')
	{
		if (str[1] && str[1] == '<')
			add_two(str, list, i, TOKEN_REDIR_IN);
		else
			add_one(str, list, i, TOKEN_HEREDOC);
	}
	else if (str[0] == '|')
	{
		if (str[1])
			if (str[1]  == '|'){
				add_two(str, list, i, TOKEN_OR);
				index = 1;}

		if(index == 0)
			add_one(str, list, i, TOKEN_PIPE);
	}
	else if (str[0] == '>')
	{
		if (str[1] && str[1] == '>')
			add_two(str, list, i, TOKEN_REDIR_APPEND);
		else
			add_one(str, list, i, TOKEN_REDIR_OUT);
	}
	else if(str[0] == '&')
	{
		if (str[1] && str[1] == '&')
			add_two(str, list, i, TOKEN_AND);
		else
			exit(write(2, "ERROR!\n", 7));
	}
}