/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:17:58 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/17 08:08:12 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node_arbre	*new_sub(t_node_arbre *racine)
{
	t_node_arbre	*node;

	node = my_malloc(sizeof(t_node_arbre), 1);
	if (!node)
		return (NULL);
	node->arbre = c_arbre();
	if (!node->arbre)
		return (NULL);
	node->arbre->racine = racine;
	node->mode = TOKEN_PARENTHESE;
	return (node);
}

t_node_arbre	*parse_parenthese(t_node **tmp)
{
	t_node_arbre	*node;

	*tmp = (*tmp)->next;
	while ((*tmp)->value[0] != ')')
	{
		node = new_sub(parse_and_or(tmp));
		if (!node)
			return (NULL);
	}
	*tmp = (*tmp)->next;
	return (node);
}

t_node_arbre	*parse_cmd(t_node **tmp)
{
	t_node			*node;
	t_node_arbre	*arbre_node;

	arbre_node = 0;
	if ((*tmp)->mode == TOKEN_PARENTHESE && (*tmp)->value[0] == '(')
		return (parse_parenthese(tmp));
	if ((*tmp)->mode == TOKEN_EXPR)
	{
		node = *tmp;
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
			*tmp = (*tmp)->next;
		arbre_node = add_commade(node);
		if (!arbre_node)
			return (NULL);
		return (arbre_node);
	}
	return (NULL);
}

bool ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;	
	}
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);	
}

bool	open_herdoc(t_nnode *node)
{
	char *str = NULL;
	char *file;
	static int n;
	int		fd;

	file = ft_strjoin("file",ft_itoa(n));
	fd = open(file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (printf("hna"),0);
	n++;
	while (1)
	{
		str = readline("heredoc> ");
		if (node->next)
		{
			if (ft_strcmp(node->next->value,str))
				break;
			str = ft_strjoin(str, "\n");
			write(fd, str, ft_strlen(str));
		}
	}
	return (1);
}

t_node_arbre	*parse_redir(t_node **tmp)
{
	t_node_arbre	*node_left;
	t_node_arbre	*node;
	t_nnode			*i_node = NULL;

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
				if (!open_herdoc(i_node))
					return (0);
				if (i_node->next)
					i_node->next->value = "file0";
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
		while ((*tmp) && (*tmp)->mode == TOKEN_EXPR)
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
