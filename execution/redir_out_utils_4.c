/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:53:41 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/25 17:57:03 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_m_error(char *str)
{
	ft_printf("minishell: ", str);
	ft_printf(": ", strerror(errno));
	(1) && (ft_printf("\n", NULL), ft_status(1, 1), 0);
}

int	open_outfile(struct s_nnode *wnt, int *fd, int *j, t_env *env)
{
	char	*backup;

	if (wnt->flag_expend == 1 || wnt->flag_expend == 2)
	{
		backup = ft_strdup(wnt->value);
		wnt->value = ft_expand(env, wnt->value);
		if (!wnt->value)
		{
			(1) && (ft_printf("minishell: ", backup), ft_status(1, 1));
			ft_printf(": ", ": ambiguous redirect\n");
			return (0);
		}
	}
	if (wnt->value && only_wild(wnt->value))
	{
		(1) && (ft_printf("minishell: ", wnt->value), ft_status(1, 1));
		ft_printf(": ", "ambiguous redirect\n");
		return (0);
	}
	fd[*j] = open(wnt->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[*j] == -1)
		return (ft_m_error(wnt->value), 0);
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
			(1) && (ft_printf("minishell: ", backup), ft_status(1, 1));
			ft_printf(": ", "ambiguous redirect\n");
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
		return (ft_m_error(wnt->value), 0);
	(*k)++;
	return (1);
}
