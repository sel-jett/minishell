/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:19:27 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/21 08:12:28 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ope(t_node *node)
{
	if (!node)//
		return (1);//
	if (node->mode == TOKEN_AND || node->mode == TOKEN_OR
		|| node->mode == TOKEN_PIPE || is_redir(node))
		return (1);
	return (0);
}

int	plant_5(t_node	*tmp, t_list *list)
{
	t_node	*node;
	int		index;

	node = 0;
	if (!list)
		return (0);
	while (tmp)
	{
		index = 0;
		if (tmp->mode != TOKEN_SPACE)
		{
			node = c_cpynode(tmp, list->tail, list);
			if (!node)
				return (0);
			check_wilc(node);
			add_back(list, node);
		}
		if ((tmp->prev && tmp->prev->mode == TOKEN_SPACE)
			&& tmp->prev->prev && !ope(tmp->prev->prev))
			node->flag_space = 1;
		if (tmp->list_arg && tmp->list_arg->top)
		{
			node->flag_expend = 1;
			if (tmp->mode == TOKEN_EXPR)
				node->flag_expend = 2;
		}
		tmp = tmp->next;
	}
	tmp = list->top;
	while (tmp)
	{
		if (tmp->mode == TOKEN_Double_Q || tmp->mode == TOKEN_Single_Q)
		{
			if (tmp->mode == TOKEN_Double_Q)
			{
				tmp->flag_quote = 1;
				if (tmp->list_arg && tmp->list_arg->top)
					node->flag_expend = 1;
			}
			if (tmp->mode == TOKEN_Single_Q)
				tmp->flag_quote = 2;
			tmp->mode = TOKEN_EXPR;
		}
		tmp = tmp->next;
	}
	return (1);
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

bool	open_herdoc(t_nnode *node, char **file)
{
	char		*str;
	int			n;
	int			fd;

	(1) && (str = 0, n = 0);
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
	while (1)
	{
		str = readline("heredoc> ");
		if (node->next)
		{
			if (ft_strcmp(node->next->value, str))
				break ;
			str = ft_strjoin2(str, "\n");
			write(fd, str, ft_strlen(str));
		}
		free(str);
	}
	if (str)
		(1) && (free(str), str = NULL);
	return (1);
}
