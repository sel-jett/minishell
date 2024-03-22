/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:07:13 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 08:12:01 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execve(char *env_var, char **env, char **cmmd)
{
	if (execve(env_var, cmmd, env) == -1)
	{
		ft_printf("minishell: ", cmmd[0]);
		ft_printf(": ", NULL);
		perror("");
		exit(126);
	}
}

char	**linkedlist_to_arr(t_node *tree)
{
	char	**arr;
	int		i;
	t_node	*tree_tmp;
	t_node	*tmp;
	t_node	*smp;

	tree_tmp = tree;
	tmp = tree;
	smp = tree;
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
	while (tmp)
	{
		if (!(tmp->value)[0] && i > 0 && tmp->flag_space == 0)
		{
			tmp = tmp->next;
			if (!tmp)
				break ;
			arr[i] = ft_strjoin(arr[i], "\\");
			tmp->flag_space = 1;
		}
		if (!tmp->flag_space)
		{
			arr[i] = ft_strjoin(arr[i], tmp->value);
			if (!arr[i])
				return (NULL);
		}
		else if (tmp->flag_space == 1)
		{
			i++;
			arr[i] = ft_strjoin(arr[i], tmp->value);
			if (!arr[i])
				return (NULL);
		}
		tmp = tmp->next;
	}
	i++;
	arr[i] = NULL;
	return (arr);
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

char	**redirlist_to_arr(t_nlist *tree)
{
	char	**arr;
	int		i;
	int		j;
	t_nlist	*tree_tmp;
	t_nlist	*tmp;
	t_nlist	*smp;

	tree_tmp = tree;
	tmp = tree;
	smp = tree;
	i = liked_size_redir(tree_tmp);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	if (!arr)
		return (NULL);
	while (i >= 0)
	{
		arr[i] = NULL;
		i--;
	}
	i = 0;
	while (tmp->top)
	{
		j = i;
		if (!tmp->top->flag_space && tmp->top->avant_ == 1)
		{
			arr[i] = ft_strjoin(arr[i], tmp->top->value);
			if (!arr[i])
				return (NULL);
		}
		else if (tmp->top->flag_space == 1 && ft_strncmp(tmp->top->value, ">") \
				&& ft_strncmp(tmp->top->value, ">>") && \
				ft_strncmp(tmp->top->value, "<"))
		{
			if (arr[i])
				i++;
			arr[i] = ft_strjoin(arr[i], tmp->top->value);
			if (!arr[i])
				return (NULL);
		}
		if (i > j)
		{
			if (tmp->top->flag_wilc)
			{
				arr[i] = ft_strdup(ft_execute_wild(arr[i]));
				if (!arr[i])
					return (NULL);
			}
		}
		tmp->top = tmp->top->next;
	}
	i++;
	arr[i] = NULL;
	arr = array_dupper(arr);
	return (arr);
}
