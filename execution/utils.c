/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:07:13 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/17 05:54:23 by sel-jett         ###   ########.fr       */
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

char	**env_to_arr(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_strjoin(tmp->key, "=");
		arr[i] = ft_strjoin(arr[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		dprintf(2, "%s\n", arr[i]);
		i++;
	}
}

int	liked_size(t_node *tree)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = tree;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// char	**linkedlist_to_arr(t_node *tree)
// {
// 	char	**arr;
// 	int		i;
// 	t_node	*tree_tmp;
// 	t_node	*tmp;

// 	tree_tmp = tree;
// 	tmp = tree;
// 	i = liked_size(tree_tmp);
// 	arr = my_malloc(sizeof(char *) * (i + 1), 1);
// 	i = 0;
// 	while (tmp)
// 	{
// 		arr[i] = ft_strdup(tmp->value);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }


char	**linkedlist_to_arr(t_node *tree)
{
	// static int oop;
	char	**arr;
	int		i;
	t_node	*tree_tmp;
	t_node	*tmp;

	tree_tmp = tree;
	tmp = tree;
	i = liked_size(tree_tmp);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	while (i >= 0)
	{
		arr[i] = NULL;
		i--;
	}
	i = 0;
	while(tmp)
	{
		if (!tmp->flag_space)
		{
			arr[i] = ft_strjoin(arr[i], tmp->value);
		}
		else if (tmp->flag_space == 1)
		{
			i++;
			arr[i] = ft_strjoin(arr[i], tmp->value);
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
	t_nlist	*tree_tmp;
	t_nlist	*tmp;

	tree_tmp = tree;
	tmp = tree;
	i = liked_size_redir(tree_tmp);
	arr = my_malloc(sizeof(char *) * (i + 1), 1);
	while (i >= 0)
	{
		arr[i] = NULL;
		i--;
	}
	i = 0;
	while(tmp->top)
	{
		if (!tmp->top->flag_space && tmp->top->avant_ == 1)
		{
			arr[i] = ft_strjoin(arr[i], tmp->top->value);
		}
		else if (tmp->top->flag_space == 1 && ft_strncmp(tmp->top->value, ">") && ft_strncmp(tmp->top->value, ">>") && ft_strncmp(tmp->top->value, "<"))
		{
			i++;
			arr[i] = ft_strjoin(arr[i], tmp->top->value);
		}
		tmp->top = tmp->top->next;
	}
	i++;
	arr[i] = NULL;
	return (arr);
}