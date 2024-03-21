/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:19:27 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 08:37:03 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ope(t_node *node)
{
	if (!node)
		return (1);
	if (node->mode == TOKEN_AND || node->mode == TOKEN_OR
		|| node->mode == TOKEN_PIPE || is_redir(node))
		return (1);
	return (0);
}

t_node_arbre	*parse_redir(t_node **tmp)
{
	t_node_arbre	*node_left;
	t_node_arbre	*node;
	t_nnode			*i_node;
	char			*file;

	(1) && (i_node = 0, file = 0);
	node_left = parse_cmd(tmp);
	if (*tmp && is_redir(*tmp))
	{
		if ((*tmp)->mode == TOKEN_HEREDOC)
			(*tmp)->mode = TOKEN_REDIR_IN;
		i_node = (*tmp)->list_redir->top;
		while (i_node)
		{
			if (i_node->mode == TOKEN_HEREDOC)
			{
				if (!open_herdoc(i_node, &file))
					return (0);
				if (i_node->next)
					i_node->next->value = file;
				i_node->value = "<";
				i_node->mode = TOKEN_REDIR_IN;
			}
			i_node = i_node->next;
		}
		node = c_node_arbre(*tmp);
		if (!node)
			return (NULL);
		node->list_redir = c_nlist();
		if (!node->list_redir)
			return (NULL);
		node->list_redir = (*tmp)->list_redir;
		node->left = node_left;
		*tmp = (*tmp)->next;
		while ((*tmp) && (*tmp)->mode != TOKEN_PIPE && (*tmp)->mode
			!= TOKEN_AND && (*tmp)->mode != TOKEN_OR)
			*tmp = (*tmp)->next;
		return (node);
	}
	return (node_left);
}

t_node_arbre	*new_node(int mode, t_node_arbre *left, t_node_arbre *right)
{
	t_node_arbre	*node;

	if (!right)
		return (NULL);
	node = my_malloc(sizeof(t_node_arbre), 1);
	if (!node)
		return (NULL);
	node->mode = mode;
	node->left = left;
	node->right = right;
	return (node);
}

int	read_line_herdoc(int fd, t_nnode *node)
{
	char	*str;

	str = 0;
	while (1)
	{
		str = readline("heredoc> ");
		if (node->next)
		{
			if (ft_strcmp(node->next->value, str))
				break ;
			str = ft_strjoin2(str, "\n");
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

bool	open_herdoc(t_nnode *node, char **file)
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
	read_line_herdoc(fd, node);
	return (1);
}
