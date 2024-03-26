/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:07:13 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 01:00:36 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**linkedlist_to_arr(t_node *tree, t_env *exp)
{
	char	**arr;
	int		i;
	t_node	*tree_tmp;
	t_node	*tmp;

	tree_tmp = tree;
	tmp = tree;
	i = liked_size(tree_tmp);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	if (!arr)
		return (NULL);
	while (i >= 0)
	{
		arr[i] = NULL;
		i--;
	}
	i = 0;
	return (arr_filler(tmp, arr, i, exp));
}

static int	liked_size_redir(t_nlist *tree)
{
	int		i;
	t_nnode	*tmp;

	i = 0;
	tmp = tree->top;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	arr_filler_redir(t_nnode *tmp, char **arr, int *i)
{
	if (!tmp->flag_space && tmp->avant_ == 1)
	{
		arr[*i] = ft_strjoin(arr[*i], tmp->value);
		if (!arr[*i])
			return (0);
	}
	else if (tmp->flag_space == 1 && ft_strncmp(tmp->value, ">") \
			&& ft_strncmp(tmp->value, ">>") && \
			ft_strncmp(tmp->value, "<"))
	{
		if (arr[*i])
			(*i)++;
		arr[*i] = ft_strjoin(arr[*i], tmp->value);
		if (!arr[*i])
			return (0);
	}
	return (1);
}

char	**redir_malloc(t_nlist	*tree_tmp)
{
	int		i;
	char	**arr;

	i = liked_size_redir(tree_tmp);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	if (!arr)
		return (NULL);
	while (i >= 0)
	{
		arr[i] = NULL;
		i--;
	}
	return (arr);
}

char	**redirlist_to_arr(t_nlist *tree)
{
	char	**arr;
	int		i;
	int		j;
	int		check;
	t_nlist	*tree_tmp;

	(1) && (i = 0, tree_tmp = tree, arr = redir_malloc(tree_tmp));
	if (!arr)
		return (NULL);
	while (tree->top)
	{
		(1) && (j = i, check = 0);
		if (!arr_filler_redir(tree->top, arr, &i))
			return (NULL);
		if (i > j)
		{
			if (tree->top->flag_wilc)
				(1) && (arr[i] = ft_strdup(ft_execute_wild(arr[i])), check = 1);
			if (check == 1 && !arr[i])
				return (NULL);
		}
		tree->top = tree->top->next;
	}
	return (i++, arr[i] = NULL, array_dupper(arr));
}
