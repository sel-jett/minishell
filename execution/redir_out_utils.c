/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:03:34 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/26 10:55:15 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_cmd(t_node_arbre *tree)
{
	int	i;

	i = 0;
	while (tree->list_redir->top)
	{
		if (tree->list_redir->top->avant_ == 1 || \
			(tree->list_redir->top->avant_ == 0 && \
				ft_strncmp(tree->list_redir->top->value, ">") && \
					ft_strncmp(tree->list_redir->top->value, ">>") && \
						ft_strncmp(tree->list_redir->top->value, "<")))
			i++;
		tree->list_redir->top = tree->list_redir->top->next;
	}
	return (i);
}

char	**ft_tree_to_cmd(t_node_arbre *tree)
{
	int				i;
	char			**cmmd;
	struct s_nnode	*tmp;

	tmp = tree->list_redir->top;
	i = ft_count_cmd(tree);
	cmmd = my_malloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	tree->list_redir->top = tmp;
	while (tree->list_redir->top)
	{
		if (tree->list_redir->top->avant_ == 1 || \
			(tree->list_redir->top->avant_ == 0 && \
			ft_strncmp(tree->list_redir->top->value, ">") && \
			ft_strncmp(tree->list_redir->top->value, ">>") && \
			ft_strncmp(tree->list_redir->top->value, "<")))
		{
			cmmd[i] = ft_strdup(tree->list_redir->top->value);
			i++;
		}
		tree->list_redir->top = tree->list_redir->top->next;
	}
	cmmd[i] = NULL;
	return (cmmd);
}

void	ft_execute_redir(t_node_arbre *tree, t_env **env, t_env **exp)
{
	int				i;
	char			**cmmd;
	char			**path;
	char			**envp;

	envp = env_to_arr(*env);
	path = ft_split(get_path(*env), ':');
	cmmd = redirlist_to_arr(tree->list_redir);
	i = 0;
	while (cmmd[i])
	{
		cmmd[i] = ft_expand(*env, cmmd[i]);
		i++;
	}
	if (is_builtin(cmmd[0]))
	{
		ft_builtin(cmmd, env, exp);
		return ;
	}
	ft_execute_child(envp, cmmd, path);
}

int	*get_files(struct s_nnode *list)
{
	int				*fd;
	struct s_nnode	*tmp;
	int				i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->avant_ == 2)
			i++;
		tmp = tmp->next;
	}
	tmp = list;
	fd = my_malloc(sizeof(int) * (i + 1), 1);
	i = 0;
	while (tmp)
	{
		(tmp->avant_ == 2) && (fd[i] = 0, i++, 0);
		tmp = tmp->next;
	}
	fd[i] = -100;
	return (fd);
}

void	ft_close_fd(int *fd)
{
	int	i;

	i = 0;
	while (fd[i] != -100)
	{
		if (fd[i] == 0)
		{
			i++;
			continue ;
		}
		close(fd[i]);
		fd[i] = -100;
		i++;
	}
}
