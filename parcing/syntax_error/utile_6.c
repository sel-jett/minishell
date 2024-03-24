/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:19:27 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/24 05:42:05 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_text2(t_nnode *tmp)
{
	if (tmp->mode == TOKEN_EXPR || tmp->mode == TOKEN_Double_Q
		|| tmp->mode == TOKEN_Single_Q)
		return (1);
	return (0);
}

void	ft_count(t_nnode *node, int *len, int *index)
{
	int	i;

	while (node && is_text2(node))
	{
		if (node->mode != TOKEN_EXPR)
			*index = 1;
		i = 0;
		while (node->value[i])
		{
			i++;
			(*len)++;
		}
		if (node->flage_space_ap == 1)
			break ;
		node = node->next;
	}
}

char	*cancat(t_nnode *node, int *index)
{
	int		len;
	int		i;
	char	*str;
	t_nnode	*tmp;

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

void	handler(int signal)
{
	extern int x;

	if (signal == SIGINT)
		close(0);
}

int	read_line_herdoc(int fd, t_nnode *node, t_env *exp, int *n)
{
	char		*str;
	int			index;
	extern int	x;

	// igno_sig();
	signal(SIGINT, handler);
	(1) && (index = 0, str = 0);
	while (1)
	{
		str = readline("heredoc> ");
		if (!str)
			break ;
		if (node->next)
		{
			if (ft_strcmp(cancat(node->next, &index), str))
				break ;
			str = ft_strjoin2(str, "\n");
			if (!str)
				return (0);
			if (index == 0)
				str = ft_expand(exp, str);
			if (!str)
				return (0);
			write(fd, str, ft_strlen(str));
		}
		free(str);
	}
	if (str)
		(1) && (free(str), str = NULL);
	if (ttyname(0) == 0)
	{
		*n = 1;
		fd = open(ttyname(1), O_RDONLY);
		dup2(0, fd);
	}
	return (1);
}

bool	open_herdoc(t_nnode *node, char **file, t_env *exp, int *m)
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
