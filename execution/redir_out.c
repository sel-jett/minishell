/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:12:12 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/18 02:36:48 by sel-jett         ###   ########.fr       */
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
		if (tree->list_redir->top->avant_ == 1 || (tree->list_redir->top->avant_ == 0 && \
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

	// exit(0);
	envp = env_to_arr(*env);
	path = ft_split(get_path(*env), ':');
		// dprintf(2, "[%s]\n", tree->list_redir->top->value);
		// exit(0);
	// while (tree->list_redir->top)
	// {
	// 	// dprintf(2, "[%s]\n", tree->list_redir->top->value);
	// 	dprintf(2, "[%s][%d][%d]\n", tree->list_redir->top->value, tree->list_redir->top->avant_, \
	// 	tree->list_redir->top->flag_space);
	// 	tree->list_redir->top = tree->list_redir->top->next;
	
	// }
	// exit(0);
	// exit(0);
	cmmd = redirlist_to_arr(tree->list_redir);
	// i = 0;
	// while (cmmd[i])
	// {
	// 	dprintf(2, "[][%s][]\n", cmmd[i]);
	// 	i++;
	// }
	// exit(0);
	// cmmd = ft_tree_to_cmd(tree);
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
		if (tmp->avant_ == 2)
		{
			fd[i] = 0;
			i++;
		}
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
		close(fd[i]);
		i++;
	}
}

int	*ft_redir_in_files(struct s_nnode *list)
{
	int				*fd;
	struct s_nnode	*tmp;
	int				i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->avant_ == 3)
			i++;
		tmp = tmp->next;
	}
	tmp = list;
	fd = my_malloc(sizeof(int) * (i + 1), 1);
	i = 0;
	while (tmp)
	{
		if (tmp->avant_ == 3)
			i++;
		tmp = tmp->next;
	}
	fd[i] = -100;
	return (fd);
}

int	*ft_append_files(struct s_nnode *list)
{
	int				*fd;
	struct s_nnode	*tmp;
	int				i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->avant_ == 4)
			i++;
		tmp = tmp->next;
	}
	tmp = list;
	fd = my_malloc(sizeof(int) * (i + 1), 1);
	i = 0;
	while (tmp)
	{
		if (tmp->avant_ == 4)
		{
			fd[i] = 0;
			i++;
		}
		tmp = tmp->next;
	}
	fd[i] = -100;
	return (fd);
}

void	files_dupper(int *fd, int *sd, int *ad, struct s_nnode	*cnt)
{
	int	i;
	int	j;
	int	k;
	int	f;

	i = 0;
	j = 0;
	k = 0;
	f = 0;
	while (fd && fd[i] != -100)
		i++;
	while (sd && sd[j] != -100)
		j++;
	while (ad && ad[k] != -100)
		k++;
	while (cnt)
	{
		if (!ft_strncmp(cnt->value, ">"))
			f = 1;
		else if (!ft_strncmp(cnt->value, ">>"))
			f = 2;
		cnt = cnt->next;
	}
	if (f == 1)
		dup2(fd[i - 1], 1);
	else if (f == 2)
		dup2(ad[k - 1], 1);
	if (sd && j > 0)
	{
		dup2(sd[j - 1], 0);
	}
}

void	ft_execute_redir_out(t_node_arbre *tree, t_env	*env, t_env *exp)
{
	int				*fd;
	int				*sd;
	int				*ad;
	struct s_nnode	*tmp;
	struct s_nnode	*smp;
	struct s_nnode	*amp;
	struct s_nnode	*cnt;
	struct s_nnode	*wnt;
	int				orig_stdout;
	int				orig_stdin;
	char			*backup;
	int				i = 0;
	int				j = 0;
	int				k = 0;

	orig_stdout = dup(1);
	orig_stdin = dup(0);
	if (!ft_strncmp(tree->list_redir->top->value, ">>") || \
		!ft_strncmp(tree->list_redir->top->value, ">") || \
		!ft_strncmp(tree->list_redir->top->value, "<"))
		tree->list_redir->top = tree->list_redir->top->next;
	tmp = tree->list_redir->top;
	smp = tree->list_redir->top;
	amp = tree->list_redir->top;
	cnt = tree->list_redir->top;
	wnt = tree->list_redir->top;
	ad = ft_append_files(amp);
	sd = ft_redir_in_files(smp);
	fd = get_files(tmp);
	while (wnt)
	{
		if (wnt->avant_ == 3)
		{
			if (wnt->flag_expend == 1 || wnt->flag_expend == 2)
			{
				backup = ft_strdup(wnt->value);
				wnt->value = ft_strdup(ft_expand(env, wnt->value));
				if (!wnt->value)
				{
					ft_printf("minishell: ", backup);
					ft_printf(": ", "ambiguous redirect");
					ft_printf("\n", NULL);
					return ;
				}
			}
			sd[i] = open(wnt->value, O_RDONLY);
			if (sd[i] == -1)
			{
				ft_printf("minishell: ", wnt->value);
				ft_printf(": ", strerror(errno));
				ft_printf("\n", NULL);
				return ;
			}
			i++;
		}
		else if (wnt->avant_ == 2)
		{
			if (wnt->flag_expend == 1 || wnt->flag_expend == 2)
			{	
				backup = ft_strdup(wnt->value);
				wnt->value = ft_strdup(ft_expand(env, wnt->value));
				if (!wnt->value)
				{
					ft_printf("minishell: ", backup);
					ft_printf(": ", "ambiguous redirect");
					ft_printf("\n", NULL);
					return ;
				}
			}
			fd[j] = open(wnt->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd[j] == -1)
			{
				ft_printf("minishell: ", wnt->value);
				ft_printf(": ", "ambiguous redirect");
				ft_printf("\n", NULL);
				return ;
			}
			j++;
		}
		else if (wnt->avant_ == 4)
		{
			if (wnt->flag_expend == 1 || wnt->flag_expend == 2)
			{
				backup = ft_strdup(wnt->value);
				wnt->value = ft_strdup(ft_expand(env, wnt->value));
				if (!wnt->value)
				{
					ft_printf("minishell: ", backup);
					ft_printf(": ", strerror(errno));
					ft_printf("\n", NULL);
					return ;
				}
			}
			ad[k] = open(wnt->value, O_CREAT | O_WRONLY | O_APPEND , 0644);
			if (ad[k] == -1)
			{
				ft_printf("minishell: %s", wnt->value);
				ft_printf(": %s\n", strerror(errno));
				return ;
			}
			k++;
		}
		wnt = wnt->next;
	}
	files_dupper(fd, sd, ad, cnt);
	if (fd)
		ft_close_fd(fd);
	if (sd)
		ft_close_fd(sd);
	if (ad)
		ft_close_fd(ad);
	ft_execute_redir(tree, &env, &exp);
	dup2(orig_stdout, 1);
	dup2(orig_stdin, 0);
}
