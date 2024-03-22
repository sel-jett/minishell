/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:04:03 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/21 22:04:22 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *tmp)
{
	while (tmp)
	{
		printf("%s", tmp->key);
		printf("=");
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	ft_status(0, 1);
}
