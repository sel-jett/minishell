/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:53:11 by amel-has          #+#    #+#             */
/*   Updated: 2024/03/25 12:57:45 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handel_signel_(struct sigaction sa)
{
	// rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	read_parse(int *index, t_list *list, t_env *exp, int *n)
{
	int	i;

	i = 0;
	while (list->str[i])
	{
		if (!plants(list, &i))
		{
			*index = 1;
			break ;
		}
	}
	if (!*index)
		if (!plant_4(list, exp, n))
			*index = 1;
}
