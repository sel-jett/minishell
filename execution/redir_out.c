/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:12:12 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 15:52:37 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_outfile(struct s_nnode *wnt, int *fd, int *j, t_env *env)
{
	char	*backup;

	if (wnt->flag_expend == 1 || wnt->flag_expend == 2)
	{
		backup = ft_strdup(wnt->value);
		wnt->value = ft_expand(env, wnt->value);
		if (!wnt->value)
		{
			ft_printf("minishell: ", backup);
			ft_printf(": ", "ambiguous redirect\n");
			ft_status(1, 1);
			return (0);
		}
	}
	if (wnt->value && only_wild(wnt->value))
	{
		ft_printf("minishell: ", wnt->value);
		ft_printf(": ", "ambiguous redirect\n");
		ft_status(1, 1);
		return (0);
	}
	fd[*j] = open(wnt->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[*j] == -1)
	{
		ft_printf("minishell: ", wnt->value);
		ft_printf(": ", strerror(errno));
		ft_printf("\n", NULL);
		ft_status(1, 1);
		return (0);
	}
	(*j)++;
	return (1);
}

int	open_appendfile(struct s_nnode *wnt, int *ad, int *k, t_env *env)
{
	char	*backup;

	if (wnt->flag_expend == 1 || wnt->flag_expend == 2)
	{
		backup = ft_strdup(wnt->value);
		wnt->value = ft_expand(env, wnt->value);
		if (!wnt->value)
		{
			ft_printf("minishell: ", backup);
			ft_printf(": ", "ambiguous redirect\n");
			ft_status(1, 1);
			return (0);
		}
	}
	if (wnt->value && only_wild(wnt->value))
	{
		ft_printf("minishell: ", wnt->value);
		ft_printf(": ", "ambiguous redirect\n");
		ft_status(1, 1);
		return (0);
	}
	ad[*k] = open(wnt->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (ad[*k] == -1)
	{
		ft_printf("minishell: %s", wnt->value);
		ft_printf(": %s\n", strerror(errno));
		ft_status(1, 1);
		return (0);
	}
	(*k)++;
	return (1);
}

int	loop_opener(struct s_nnode *wnt, t_files *file, t_env *env)
{
	int	i;
	int	j;
	int	k;

	(1) && (i = 0, j = 0, k = 0);
	while (wnt)
	{
		if (wnt->avant_ == 3)
		{
			if (!open_infile(wnt, file->sd, &i, env))
				return (0);
		}
		else if (wnt->avant_ == 2)
		{
			if (!open_outfile(wnt, file->fd, &j, env))
				return (0);
		}
		else if (wnt->avant_ == 4)
		{
			if (!open_appendfile(wnt, file->ad, &k, env))
				return (0);
		}
		wnt = wnt->next;
	}
	return (1);
}

int	files_opener(t_node_arbre *tree, t_files *file, t_env	*env)
{
	struct s_nnode	*tmp;
	struct s_nnode	*smp;
	struct s_nnode	*amp;
	struct s_nnode	*wnt;
	int				i;

	tmp = tree->list_redir->top;
	smp = tree->list_redir->top;
	amp = tree->list_redir->top;
	wnt = tree->list_redir->top;
	file->ad = ft_append_files(amp);
	file->sd = ft_redir_in_files(smp);
	file->fd = get_files(tmp);
	i = loop_opener(wnt, file, env);
	if (!i)
	{
		if (file->fd)
			ft_close_fd(file->fd);
		if (file->sd)
			ft_close_fd(file->sd);
		if (file->ad)
			ft_close_fd(file->ad);
		return (0);
	}
	return (1);
}

void	ft_close_all(t_files *file, int out_or, int in_or)
{
	(file->fd) && (ft_close_fd(file->fd), 0);
	(file->sd) && (ft_close_fd(file->sd), 0);
	(file->ad) && (ft_close_fd(file->ad), 0);
	close(out_or);
	close(in_or);
}

void	ft_execute_redir_out(t_node_arbre *tree, t_env	*env, t_env *exp)
{
	t_files			*file;
	struct s_nnode	*cnt;
	int				orig_stdout;
	int				orig_stdin;

	file = my_malloc(sizeof(t_files), 1);
	orig_stdout = dup(1);
	orig_stdin = dup(0);
	cnt = tree->list_redir->top;
	if (!files_opener(tree, file, env))
	{
		ft_status(1, 1);
		ft_close_all(file, orig_stdout, orig_stdin);
		return ;
	}
	files_dupper(file->fd, file->sd, file->ad, cnt);
	(file->fd) && (ft_close_fd(file->fd), 0);
	(file->sd) && (ft_close_fd(file->sd), 0);
	(file->ad) && (ft_close_fd(file->ad), 0);
	ft_execute_redir(tree, &env, &exp);
	dup2(orig_stdout, 1);
	dup2(orig_stdin, 0);
	close(orig_stdout);
	close(orig_stdin);
}
