/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:19:17 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 17:09:53 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	oxe_check_entre_parentheses(t_node *node)
{
	if (node && node->prev && node->prev->mode == TOKEN_SPACE)
	{
		if (node && node->prev && node->prev->prev
			&& (is_text(node->prev->prev) || is_redir(node->prev->prev)))
			return (0);
	}
	return (1);
}

int	check_enter_parentheses(t_node *node)
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	if (!oxe_check_entre_parentheses(node))
		return (0);
	else if ((node && node->prev)
		&& (is_text(node->prev) || is_redir(node->prev)))
		return (0);
	if (node && node->next)
		node = node->next;
	while (node && node->value[0] != ')')
	{
		if (is_empty(node->value))
			j++;
		i++;
		node = node->next;
	}
	if (i == j)
		return (0);
	if (i)
		return (1);
	return (0);
}

int	check_apres_parentheses(t_node *node)
{
	if (node && node->next && node->next->mode == TOKEN_SPACE)
	{
		if (node && node->next && node->next->next
			&& (is_text(node->next->next) || (node->next->next->mode
					== TOKEN_PARENTHESE && node->next->next->value[0] == '(')))
			return (0);
	}
	else if ((node && node->next)
		&& (is_text(node->next) || (node->next->mode
				== TOKEN_PARENTHESE && node->next->value[0] == '(')))
		return (0);
	return (1);
}

int	check_exp(t_node *tmp)
{
	int	i;

	i = 0;
	while (tmp->value && tmp->value[i])
	{
		if (tmp->value[i] != '!')
			return (1);
		i++;
	}
	if (tmp->prev && tmp->prev->value && tmp->prev->value[0] == '(')
		return (1);
	return (0);
}

int	open_tty(int *n)
{
	int	fd;

	if (ttyname(0) == 0)
	{
		*n = 1;
		fd = open(ttyname(1), O_RDONLY);
		if (fd == -1)
			return (0);
		if (dup2(0, fd) == -1)
			return (close(fd),0);
		ft_status(1, 1);
	}
	return (1);
}
