/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:22:32 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/24 16:17:52 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	oxe1(t_node	*node, t_node *tmp1, t_nnode *redir_node)
{
	if (node && node->prev)
	{
		tmp1 = node->prev;
		// exit(0);
		// printf("%p\n",&tmp1);
		// printf("%p\n",&tmp1->prev);
		// printf("++++++++++++++\n");
		// printf("++++++++++%d\n",node->prev->mode);
		// 	printf("+++++++++++++\n");
		// printf("%p\n",&);
		// printf("%p\n",&);
		// if (tmp1->prev->mode != TOKEN_AND)
		// 	exit(2);
			
			// printf("################################");
		while (tmp1 && tmp1->prev && (tmp1->prev->mode != TOKEN_AND
				&& tmp1->prev->mode != TOKEN_OR
				&& tmp1->prev->mode != TOKEN_PIPE && tmp1->prev->mode != TOKEN_PARENTHESE))
		{
			// exit(1);
			tmp1 = tmp1->prev;
		}
		while (tmp1 && !is_redir(tmp1))
		{
			if (tmp1->mode != TOKEN_SPACE)
			{
				tmp1->avant_ = 1;
				redir_node = c_nnode(tmp1);
				if (!redir_node)
					return (0);
				if (tmp1->prev && tmp1->prev->mode == TOKEN_SPACE
					&& !ope(tmp1->prev->prev))
					redir_node->flag_space = 1;
				add_nback(node->list_redir, redir_node);
			}
			tmp1 = tmp1->next;
		}
	}
	return (1);
}

static void	oxe2(t_node *tmp)
{
	int	i;

	i = 0;
	while (tmp->value && tmp->value[i])
	{
		if (tmp->value && tmp->value[i] == '$')
		{
			tmp->flag_expend = 1;
			if (tmp->mode == TOKEN_EXPR)
				tmp->flag_expend = 2;
		}
		i++;
	}
}

static	void	oxe3(t_node *tmp)
{
	if (tmp->prev && tmp->prev->prev
		&& is_redir(tmp->prev->prev) && is_text(tmp))
	{
		tmp->avant_ = 2;
		if (tmp->prev->prev->mode == TOKEN_REDIR_IN
			|| tmp->prev->prev->mode == TOKEN_HEREDOC)
			tmp->avant_ = 3;
		if (tmp->prev->prev->mode == TOKEN_REDIR_APPEND)
			tmp->avant_ = 4;
	}
	else if (tmp->prev && is_redir(tmp->prev) && is_text(tmp))
	{
		tmp->avant_ = 2;
		if (tmp->prev->mode == TOKEN_REDIR_IN
			|| tmp->prev->mode == TOKEN_HEREDOC)
			tmp->avant_ = 3;
		if (tmp->prev->mode == TOKEN_REDIR_APPEND)
			tmp->avant_ = 4;
	}
}

static int	oxe4(t_nnode	*tmp_node)
{
	while (tmp_node)
	{
		if (tmp_node->mode == TOKEN_REDIR_OUT)
			tmp_node->mode_d = 1;
		if (tmp_node->mode == TOKEN_REDIR_APPEND)
			tmp_node->mode_d = 2;
		tmp_node = tmp_node->next;
	}
	return (1);
}

int	add_list_redir(t_node *node)
{
	t_node	*tmp;
	t_nnode	*redir_node;
	t_node	*tmp1;

	(1) && (tmp = node, redir_node = 0, tmp1 = 0);
	node->list_redir = c_nlist();
	if (!node->list_redir || !oxe1(node, tmp1, redir_node))
		return (0);
	while (oxe5(tmp))
	{
		oxe2(tmp);
		if (tmp->mode != TOKEN_SPACE)
		{
			oxe3(tmp);
			redir_node = c_nnode(tmp);
			if (!redir_node)
				return (0);
			check_(tmp, redir_node);
			add_nback(node->list_redir, redir_node);
		}
		tmp = tmp->next;
	}
	return (oxe4(node->list_redir->top), 1);
}
