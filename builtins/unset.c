/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:27:43 by sel-jett          #+#    #+#             */
/*   Updated: 2024/02/03 22:29:52 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char *cmd, t_env **cnev)
{
	char	**dptr;
	int		i;

	i = 0;
	dptr = ft_split(cmd, ' ');
	while (dptr[i])
	{
		ft_list_remove_if(cnev, dptr[i], ft_strncmp_one);;
		i++;
	}
}
