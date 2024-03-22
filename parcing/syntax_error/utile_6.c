/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:19:27 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/22 07:10:20 by sel-jett         ###   ########.fr       */
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

void	ft_count(t_nnode *node, int *len)
{
	int	i;

	while (node && is_text2(node))
	{
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

char	*cancat(t_nnode *node)
{
	int		len;
	int		i;
	char	*str;
	t_nnode	*tmp;

	(1) && (len = 0, tmp = node);
	ft_count(node, &len);
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

int	read_line_herdoc(int fd, t_nnode *node, t_env *exp)
{
	char	*str;

	str = 0;
	while (1)
	{
		str = readline("heredoc> ");
		if (node->next)
		{
			if (ft_strcmp(cancat(node->next), str))
				break ;
			str = ft_strjoin2(str, "\n");
			if (!str)
				return (0);
			str = ft_expand(exp, str);
			if (!str)
				return (0);
			write(fd, str, ft_strlen(str));
		}
		free(str);
	}
	if (str)
		(1) && (free(str), str = NULL);
	return (1);
}

bool	open_herdoc(t_nnode *node, char **file, t_env *exp)
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
	read_line_herdoc(fd, node, exp);
	return (1);
}
