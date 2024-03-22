/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:41:40 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 06:04:39 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		(tmp->avant_ == 4) && (i++, 0);
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

int	ft_dup2(int fd, int std)
{
	int	i;

	i = dup2(fd, std);
	if (i == -1)
	{
		ft_printf("minishell: ", strerror(errno));
		ft_printf(": ", "dup2");
		ft_printf("\n", NULL);
		ft_status(1, 1);
	}
	return (i);
}

int	files_dupper(int *fd, int *sd, int *ad, struct s_nnode *cnt)
{
	int	i;
	int	j;
	int	k;
	int	f;

	(1) && (i = 0, j = 0, k = 0, f = 0);
	while (fd && fd[i] != -100)
		i++;
	while (sd && sd[j] != -100)
		j++;
	while (ad && ad[k] != -100)
		k++;
	while (cnt)
	{
		(cnt->mode_d == 1) && (f = 1, 0);
		(cnt->mode_d == 2) && (f = 2, 0);
		cnt = cnt->next;
	}
	(f == 1) && (i = ft_dup2(fd[i - 1], 1), 0);
	(f == 2) && (i = ft_dup2(ad[k - 1], 1), 0);
	(sd && j > 0 && i != -1) && (i = ft_dup2(sd[j - 1], 0), 0);
	return (i != -1);
}

int	open_infile(struct s_nnode *wnt, int *sd, int *i, t_env *env)
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
	sd[*i] = open(wnt->value, O_RDONLY);
	if (sd[*i] == -1)
	{
		ft_printf("minishell: ", wnt->value);
		ft_printf(": ", strerror(errno));
		ft_printf("\n", NULL);
		ft_status(1, 1);
		return (0);
	}
	(*i)++;
	return (1);
}
