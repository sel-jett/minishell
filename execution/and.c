/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amel-has <amel-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:09:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/03/22 04:03:02 by amel-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_and(t_node_arbre *tree, t_env *e, t_env *exp)
{
	execute(tree->left, e, exp);
	if (ft_status(0, 0) == 0)
		execute(tree->right, e, exp);
}
