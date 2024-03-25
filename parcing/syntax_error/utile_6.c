/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:19:27 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 18:18:01 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_text2(t_node *tmp)
{
	if (tmp->mode == TOKEN_EXPR || tmp->mode == TOKEN_Double_Q
		|| tmp->mode == TOKEN_Single_Q)
		return (1);
	return (0);
}

char	*cancat(t_node *node, int *index)
{
	int		len;
	int		i;
	char	*str;
	t_node	*tmp;

	(1) && (len = 0, tmp = node);
	ft_count(node, &len, index);
	str = my_malloc(len + 1, 1);
	if (!str)
		return (0);
	len = 0;
	while (tmp && is_text2(tmp))
	{
		i = 0;
		while (tmp->value[i])
		{
			str[len] = tmp->value[i];
			i++;
			len++;
		}
		if (tmp->flage_space_ap == 1)
			break ;
		tmp = tmp->next;
	}
	return (str[len] = '\0', str);
}

char	*herdoc_handel(t_node *i_node, char *str, t_env *exp)
{
	char	*s;
	int		index;

	index = 0;
	s = cancat(i_node, &index);
	if (!s)
		return (0);
	if (ft_strcmp(s, str))
	{
		free(str);
		str = NULL;
		return (0);
	}
	str = ft_strjoin2(str, "\n");
	(index == 0) && (str = ft_expand(exp, str));
	if (!str)
		return (0);
	return (str);
}

int	read_line_herdoc(int fd, t_node *node, t_env *exp, int *n)
{
	char		*str;
	t_node		*i_node;
	extern int	g_x;

	(1) && (i_node = NULL, str = 0, signal(SIGINT, handler));
	while (1 && g_x != 10)
	{
		i_node_make(node, &i_node);
		if (!i_node)
			break ;
		str = readline("heredoc> ");
		if (!str)
			break ;
		if (node->next && i_node)
		{
			str = herdoc_handel(i_node, str, exp);
			if (!str)
				break ;
			write(fd, str, ft_strlen(str));
		}
		free(str);
	}
	if (str)
		(1) && (free(str), str = 0);
	return (close(fd), open_tty(n));
}

bool	open_herdoc(t_node *node, char **file, t_env *exp, int *m)
{
	int			n;
	int			fd;

	(1) && (n = 0);
	while (1)
	{
		*file = ft_strjoin("/tmp/file", ft_itoa(n));
		if (access(*file, F_OK))
			break ;
		n++;
	}
	fd = open(*file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (0);
	if (!read_line_herdoc(fd, node, exp, m))
		return (0);
	return (1);
}
